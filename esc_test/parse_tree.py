import state_machine
from state_machine import FilePosition, CodeFragment

import os
import re
from collections import namedtuple, defaultdict


EventT = namedtuple('EventT', ['name', 'file_pos', 'params', 'namespace'])
def Event(name, file_pos, params=[], namespace=None): return EventT(name, file_pos, params, namespace)

Param = namedtuple('Param', ['name', 'type', 'default', 'delete'])

StateT = namedtuple('StateT', ['name', 'file_pos', 'state_type', 'statements'])

TransitionT = namedtuple('Transition', ['event_name', 'dest_state_name', 'action', 'guard', 'use_history', 'inline_dest_state', 'file_pos'])
def Transition(event_name, dest_state_name, action=None, guard=None, use_history=False, inline_dest_state=False, file_pos=None): 
    return TransitionT(event_name, dest_state_name, action, guard, use_history, inline_dest_state, file_pos)

Entry = namedtuple('Entry', ['action'])
Exit = namedtuple('Exit', ['action'])

def State(name, file_pos, state_type, statements=[]): return StateT(name, file_pos, state_type, statements)
def Region(statements): return StateT('<region>', None, 'state', statements)


class ParseError(Exception):
    def __init__(self, lineno, error_string):
        self.lineno = lineno
        self.error_string = error_string

    def format(self, path):
        prefix = '{}:{}: '.format(path, self.lineno)
        return prefix + self.error_string



def lookup_event(sm, name):
    if name == 'default':
        return state_machine.Default()
    for ev in sm.events + sm.external_events + sm.parent_file.triggered_ops:
        if ev.name == name:
            return ev


def get_string(string):
    try:
        return string.string
    except AttributeError:
        return string


def lookup_state(sm, name, src_state, connectors, lineno):
    parsed_name = name
    name = get_string(name)

    connector_number = None
    m = re.match(r'(.*)\((\d*)\)', name)
    if m:
        name = m.group(1)
        if m.group(2):
            connector_number = int(m.group(2))

    if '.' in name:
        state_name, connector_name = name.split('.')

        # check diagram connectors
        if state_name in connectors:
            if connector_name in connectors[state_name]:
                new_connector = state_machine.State(connector_name, parsed_name.file_pos, [], None, None, 'diagram connector')
                return new_connector, connector_number

        # check entry/exit connectors
        state, _ = lookup_state(sm, state_name, src_state, connectors, lineno)
        if state:
            for child in state.children:
                if child.name == connector_name:
                    return child, None

        return None, None

    candidates = []
    for st in state_machine.walk_states(sm.root_state, include_all=True):
        if st.name == name:
            candidates.append(st)
    if candidates:
        if len(candidates) > 1:
            raise ParseError(lineno, 'State name must be unique: ' + name)
        assert len(candidates) == 1
        st = candidates[0]
        return st, connector_number
    return None, None


def make_transition(source, trans, sm, connectors):
    if trans.event_name:
        if trans.event_name.startswith('tm[') and trans.event_name.endswith(']'):
            timeout = trans.event_name[3:-1]
            event = state_machine.TimerEvent(source.parent, [], timeout)
        else:
            event = lookup_event(sm, trans.event_name)
            if not event:
                raise ParseError(trans.file_pos.line, 'undefined event: %s' % trans.event_name)
    else:
        event = None

    if trans.inline_dest_state:
        dest_state = make_state(trans.dest_state_name, None, connectors, False, sm, source)
        dest_state.parent = None
        connector_number = None
    else:
        if trans.dest_state_name.string == '<internal>':
            dest_state = None
            connector_number = None
        else:
            dest_state, connector_number = lookup_state(sm, trans.dest_state_name, source, connectors, trans.file_pos.line)
            if not dest_state:
                raise ParseError(trans.file_pos.line, 'undefined state: %s' % trans.dest_state_name.string)

    if trans.use_history:
        dest_state.has_history_state = True

    guard = trans.guard if trans.guard and trans.guard.code != 'else' else None

    return state_machine.Transition(event, dest_state, trans.action, guard, trans.use_history, connector_number, trans.inline_dest_state, trans.file_pos)


def make_state(state, context, connectors, defer_transitions, sm, parent_state):
    entry_action = next((e.action for e in state.statements if isinstance(e, Entry)), None)
    exit_action = next((e.action for e in state.statements if isinstance(e, Exit)), None)
    transitions = [trans for trans in state.statements if isinstance(trans, TransitionT)]
    is_region = False
    if state.name == '<region>':
        is_region = True
    new_state = state_machine.State(state.name, state.file_pos, [], entry_action, exit_action, state.state_type)
    new_state.is_region = is_region
    new_state.parent = parent_state
    new_state.children = [make_state(child, context, connectors, defer_transitions, sm, new_state) for child in state.statements if isinstance(child, StateT)]
    for i, c in enumerate([c for c in new_state.children if c.is_region]):
        c.name = state.name + '_Region{}'.format(i + 1)

    if defer_transitions:
        context['deferred_transitions'].append((new_state, transitions))
    else:
        make_state_transitions(new_state, transitions, sm, connectors)

    return new_state


def make_state_transitions(state, transitions, sm, connectors):
    state.transitions = [make_transition(state, trans, sm, connectors) for trans in transitions]


def make_event(ev, is_triggered_op):
    return state_machine.Event(ev.name, [state_machine.Parameter(p.name, p.type, p.default, p.delete) for p in ev.params], is_triggered_op, ev.namespace)


def check_duplicate_events(events, external_events):
    definitions = {}
    for e in (events + external_events):
        if e.name in definitions:
            other_path = os.path.normpath(definitions[e.name].filename)
            own_path = os.path.normpath(e.file_pos.filename)
            message = 'conflicting event name: ' + e.name
            message += '\n    (other event definition at {}:{})'.format(other_path, definitions[e.name].line)
            raise ParseError(e.file_pos.line, message)
        definitions[e.name] = e.file_pos


def group_state_machines(state_machines):
    "Each group is one StateMachine plus zero or more SubStateMachines"
    result = []
    current_group = []

    def add_current_group(result, current_group):
        if current_group:
            result.append(list(current_group))
            del current_group[:]

    for name, is_sub_sm, statements in state_machines:
        if not is_sub_sm:
            add_current_group(result, current_group)
        current_group.append((name, statements))
    add_current_group(result, current_group)

    return result


def find_connectors(group):
    connectors = defaultdict(list)
    for name, statements in group:
        for statement in statements:
            if isinstance(statement, StateT):
                if statement.state_type == 'diagram connector':
                    connectors[name.string].append(statement.name)
    return connectors


def make_sm_file(h_includes, cpp_includes, esc_includes, events, external_events, triggered_ops, namespace, root_name, state_machines):
    check_duplicate_events(events, external_events)
    sm_file = state_machine.StateMachineFile(h_includes, cpp_includes, esc_includes,
                                             [make_event(ev, False) for ev in events],
                                             [make_event(ev, False) for ev in external_events],
                                             [make_event(tg, True) for tg in triggered_ops],
                                             namespace, root_name)
    for group in group_state_machines(state_machines):
        connectors = find_connectors(group)
        first = True
        for name, statements in group:
            is_sub_sm = not first
            first = False
            root = State(name.string, name.file_pos, None, statements)
            context = {'deferred_transitions': []}
            new_root = make_state(root, context, connectors, True, None, None)
            sm = state_machine.StateMachine(name.string, name.file_pos, new_root, is_sub_sm)
            sm_file.add_sm(sm)
            for state, transitions in context['deferred_transitions']:
                make_state_transitions(state, transitions, sm, connectors)
    return sm_file

from collections import namedtuple


class StateMachineFile(object):
    def __init__(self, h_includes, cpp_includes, esc_includes, events, external_events, triggered_ops, namespace, name):
        self.h_includes = h_includes
        self.cpp_includes = cpp_includes
        self.esc_includes = esc_includes
        self.events = events
        self.external_events = external_events
        self.triggered_ops = triggered_ops
        self.namespace = namespace
        self.name = name
        self.state_machines = []

    def add_sm(self, sm):
        sm.parent_file = self
        self.state_machines.append(sm)

    def get_states(self, name):
        states = [sm.get_state(name) for sm in self.state_machines if sm.get_state(name)]
        return states

    def to_str(self):
        h_includes = 'HIncludes\n' + ''.join(['    ' + i + '\n' for i in self.h_includes]) + '\n' if self.h_includes else ''
        cpp_includes = 'CppIncludes\n' + ''.join(['    ' + i + '\n' for i in self.cpp_includes]) + '\n' if self.cpp_includes else ''
        esc_includes = 'EscIncludes\n' + ''.join(['    ' + i + '\n' for i in self.esc_includes]) + '\n' if self.esc_includes else ''
        events = 'Events\n' + ''.join([e.to_str() + '\n' for e in self.events]) + '\n' if self.events else ''
        # Do not include external events
        triggered_ops = 'TriggeredOperations\n' + ''.join([tg.to_str() + '\n' for tg in self.triggered_ops]) + '\n' if self.triggered_ops else ''
        namespace = 'Namespace ' + self.get_namespace_str() + '\n\n' if self.namespace else ''
        state_machines = '\n\n'.join(sm.to_str() for sm in self.state_machines)
        return h_includes + cpp_includes + esc_includes + events + triggered_ops + namespace + state_machines

    def get_namespace_str(self):
        words = self.namespace.split('::')
        reserved = ['Events', 'TriggeredOperations', 'Namespace', 'StateMachine', 'HIncludes', 'CppIncludes', 'EscIncludes']
        if any(word in reserved for word in words):
            return '"' + self.namespace + '"'
        else:
            return self.namespace


FilePosition = namedtuple('FilePosition', ['filename', 'line', 'start_col', 'end_col'])


class StateMachine(object):
    def __init__(self, name, file_pos, root_state, is_sub_sm):
        self.name = name
        self.file_pos = file_pos
        self.root_state = root_state
        self.is_sub_sm = is_sub_sm
        self.root_state.parent_sm = self
        self.parent_file = None

    @property
    def prefix_name(self):
        return self.name.replace('::', '')

    @property
    def full_cpp_class_name(self):
        return self.name

    @property
    def root_name(self):
        return self.parent_file.name

    @property
    def events(self):
        return self.parent_file.events

    @property
    def external_events(self):
        return self.parent_file.external_events

    def all_states(self):
        return list(walk_states(self.root_state))

    def all_transitions(self):
        transitions = []
        for state in list(walk_states(self.root_state, include_all=True)):
            for trans in state.transitions:
                transitions.append((state, trans))
                transitions.extend([(state, t) for t in trans.all_inlined_transitions()])
        return [(s, t) for s, t in transitions if t.dest_state]

    def get_state(self, name):
        return next((s for s in self.all_states() if s.name == name), None)

    def to_str(self):
        lines = self.root_state.to_str().split('\n')
        del lines[0]
        name = 'StateMachine'
        if self.is_sub_sm:
            name = 'Sub' + name
        name += ' ' + self.name
        return name + '\n' + '\n'.join(lines)
        


class Transition(object):
    def __init__(self, event, dest_state, action, guard, use_history, connector_number=None, inline_dest_state=False, file_pos=None):
        self.event = event
        self.dest_state = dest_state
        self.action = action
        self.guard = guard
        self.use_history = use_history
        self.connector_number = connector_number
        self.inline_dest_state = inline_dest_state
        self.file_pos = file_pos

    def all_inlined_transitions(self):
        transitions = []
        if self.inline_dest_state:
            for t in self.dest_state.transitions:
                transitions.append(t)
                transitions.extend(t.all_inlined_transitions())
        return transitions


class Default(object):
    name = 'default'


Parameter = namedtuple('Parameter', ['name', 'type', 'default', 'delete'])

class Event(object):
    def __init__(self, name, params=[], is_triggered_op=False, namespace=None):
        self.name = name
        self.params = params
        self.is_triggered_op = is_triggered_op
        self.namespace = namespace

    @property
    def event_name(self):
        ret = self.name
        if self.is_triggered_op:
            ret += 'Event'
        return ret

    def to_str(self):

        def param_to_str(param):
            ret = ''
            if param.delete:
                ret += '<delete> '
            ret += param.type + ' ' + param.name
            if param.default:
                ret += ' = ' + param.default
            return ret

        ret = '    ' + self.name
        if self.params:
            if any(',' in p.type for p in self.params):
                ret += '(\n        '
                ret += ',\n        '.join([param_to_str(p) for p in self.params])
                ret += '\n    )'
            else:
                ret += '(' + ', '.join([param_to_str(p) for p in self.params]) + ')'
        return ret

    @property
    def qualified_name(self):
        if self.is_triggered_op:
            ns = ''
            if self.namespace:
                ns += '_' + self.namespace.replace('::', '_')
            return self.name + ns + '_Event'
        else:
            return self.name


class TimerEvent(object):
    def __init__(self, parent_state, params, timeout):
        self.parent_state = parent_state
        self.params = params
        self.timeout = timeout
        self.namespace = None

    @property
    def name(self):
        pname = self.parent_state.name
        return 'evTimer' + pname

    @property
    def event_name(self):
        return self.name


NullEvent = Event('evNull')


class CodeFragment(object):
    def __init__(self, code, file_pos=None):
        self.code = code
        self.file_pos = file_pos

    def __repr__(self):
        return repr(self.code)


class State(object):
    def __init__(self, name, file_pos, children, entry_action, exit_action, state_type='state'):
        self.name = name
        self.file_pos = file_pos

        self.is_junction = state_type == 'junction'
        self.is_join = state_type == 'join'
        self.is_choice = state_type == 'choice'
        self.is_entry_connector = state_type == 'entry connector'
        self.is_exit_connector = state_type == 'exit connector'
        self.is_diagram_connector = state_type == 'diagram connector'
        self.is_terminate = state_type == 'terminate'

        self.parent = None
        self.parent_sm = None
        self.children = children
        for child in self.children:
            child.parent = self
        self.transitions = []
        self.entry_action = entry_action
        self.exit_action = exit_action
        self.has_history_state = False
        self.is_region = False

    def __repr__(self):
        return 'State(' + self.name + ')'

    @property
    def has_explicit_default_transition(self):
        return next((t for t in self.transitions if isinstance(t.event, Default)), None) is not None

    @property
    def default_transition(self):
        trans = next((t for t in self.transitions if isinstance(t.event, Default)), None)
        if trans:
            return trans
        has_sub_states = bool([c for c in self.children if not (c.is_entry_connector or c.is_exit_connector or c.is_special_state or '*' in c.name)])
        if has_sub_states:
            candidate_children = [c for c in self.children if not (c.is_entry_connector or c.is_exit_connector)]
        else:
            candidate_children = [c for c in self.children if not (c.is_entry_connector or c.is_exit_connector or c.is_special_state)]
        if candidate_children and not self.is_region_root:
            return Transition(Default(), candidate_children[0], None, None, None)
        return None

    def add_child(self, child):
        assert child.parent is None
        child.parent = self
        self.children.append(child)

    def set_children(self, children):
        self.children = children
        for child in children:
            child.parent = self

    def add_transition(self, transition):
        # If the last transition is an [else] clause, keep it as the last one
        if self.transitions and self.transitions[-1].event is None and self.transitions[-1].guard is None:
            self.transitions.insert(len(self.transitions) - 1, transition)
        else:
            self.transitions.append(transition)

    @property
    def outgoing_transitions(self):
        return [t for t in self.transitions if t.dest_state]

    @property
    def sm(self):
        if self.parent_sm:
            return self.parent_sm
        else:
            return self.parent.sm

    @property
    def is_special_state(self):
        return self.is_junction or self.is_choice or self.is_join or self.is_diagram_connector

    @property
    def sub_states(self):
        return [child for child in self.children if not child.is_region and not child.is_special_state]

    @property
    def is_region_root(self):
        return any(c for c in self.children if c.is_region)

    @property
    def needs_history(self):
        if self.has_history_state:
            return True
        elif self.parent:
            return self.parent.needs_history
        else:
            return False

    @property
    def has_timer_event(self):
        return any(t for t in self.transitions if isinstance(t.event, TimerEvent))

    @property
    def timer_event(self):
        return next((t.event for t in self.transitions if isinstance(t.event, TimerEvent)), None)

    @property
    def needs_timer(self):
        return any(s for s in self.sub_states if s.has_timer_event)

    @property
    def has_null_transition(self):
        return any(t for t in self.transitions if t.event is None)

    @property
    def is_join_src_state(self):
        return len(self.outgoing_transitions) == 1 and self.outgoing_transitions[0].dest_state and self.outgoing_transitions[0].dest_state.is_join

    def to_str(self, indent=0, include_name=True):

        def ind(indent, string):
            return ' ' * indent + string + '\n'

        def make_action_str(action, ind=indent):
            if action:
                action_str = ' / '
                if '\n' in action.code:
                    action_str += '\n' + '\n'.join([' ' * ind + line for line in action.code.strip().split('\n')])
                else:
                    action_str += action.code
                return action_str
            else:
                return ''
            
        ret = ''
        name_str = self.name
        if self.is_choice:
            name_str = 'choice ' + name_str
        elif self.is_junction:
            name_str = 'junction ' + name_str
        elif self.is_join:
            name_str = 'join ' + name_str
        elif self.is_entry_connector:
            name_str = 'subentry ' + name_str
        elif self.is_exit_connector:
            name_str = 'subexit ' + name_str
        elif self.is_diagram_connector:
            name_str = 'connector ' + name_str
        elif self.is_terminate:
            name_str = 'terminate ' + name_str
        elif self.name == '':
            name_str = 'state'
        if include_name:
            ret += ind(indent, '%s' % name_str)

        if self.entry_action:
            ret += ind(indent + 4, 'entry%s' % make_action_str(self.entry_action, indent + 8))
        if self.exit_action:
            ret += ind(indent + 4, 'exit%s' % make_action_str(self.exit_action, indent + 8))

        def trans_to_str(trans):
            trigger_str = ''

            if trans.event:
                if isinstance(trans.event, TimerEvent):
                    trigger_str += 'tm[%s]' % trans.event.timeout
                else:
                    trigger_str += trans.event.name 

            if not trans.guard and not trans.event and any(t.guard for t in self.transitions if t is not trans):
                guard = 'else'
            else:
                guard = trans.guard.code if trans.guard else None

            if guard:
                trigger_str += '[%s]' % guard

            if trigger_str:
                trigger_str += ' '

            action_str = make_action_str(trans.action, indent + 8)
            if trans.inline_dest_state:
                if action_str:
                    if '\n' in action_str:
                        inline_str = 'state'
                        if trans.dest_state.is_choice:
                            inline_str = 'choice'
                        elif trans.dest_state.is_terminate:
                            inline_str = 'terminate'
                        return ind(indent + 4, '%s-> %s' % (trigger_str, inline_str))[:-1] + ' ' + \
                            make_action_str(trans.action, indent + 12).strip() + '\n' + trans.dest_state.to_str(indent + 4, include_name=False)
                    else:
                        dest_state_str = trans.dest_state.to_str(indent + 4).strip()
                        lines = ind(indent + 4, '%s-> %s' % (trigger_str, dest_state_str)).split('\n')
                        return '\n'.join([lines[0] + action_str] + lines[1:])
                else:
                    dest_state_str = trans.dest_state.to_str(indent + 4).strip()
                    return ind(indent + 4, '%s-> %s' % (trigger_str, dest_state_str))
            else:
                if not trans.dest_state:
                    return ind(indent + 4, 'internal %s%s' % (trigger_str, action_str))
                else:
                    dest_str = trans.dest_state.name
                    if trans.connector_number and trans.connector_number != 1:
                        dest_str += '(' + str(trans.connector_number) + ')'
                    if trans.use_history:
                        dest_str = 'history ' + dest_str
                    if trans.dest_state.is_entry_connector or trans.dest_state.is_diagram_connector and trans.dest_state.sm is not self.sm:
                        dest_str = trans.dest_state.parent.name + '.' + dest_str
                return ind(indent + 4, '%s-> %s%s' % (trigger_str, dest_str, action_str))

        for trans in self.transitions:
            ret += trans_to_str(trans)

        if self.is_region_root:
            ee_connectors = [c for c in self.children if c.is_entry_connector or c.is_exit_connector]
            if ee_connectors:
                for child in ee_connectors:
                    ret += child.to_str(indent + 4)
                ret += '\n'
            for child in [c for c in self.children if not c.is_entry_connector and not c.is_exit_connector]:
                if child.has_explicit_default_transition:
                    ret += trans_to_str(child.default_transition)
                for subchild in child.children:
                    ret += subchild.to_str(indent + 4)
                if not child is self.children[-1]:
                    ret += ind(indent + 4, '-----')
        else:
            for child in self.children:
                ret += child.to_str(indent + 4)
        return ret


def walk_states(state, include_all=False):
    if include_all or not state.is_special_state:
        yield state
    for child in state.children:
        for child_state in walk_states(child, include_all):
            yield child_state


def get_parent_chain(state, ancestor=None):
    while state is not ancestor and state:
        yield state
        state = state.parent


def calc_common_state(state1, state2):
    if state1 is state2:
        return state1
    chain1 = list(reversed(list(get_parent_chain(state1))))
    chain2 = list(reversed(list(get_parent_chain(state2))))
    common = None
    while chain1 and chain2 and chain1[0] is chain2[0]:
        common = chain1[0]
        chain1 = chain1[1:]
        chain2 = chain2[1:]
    return common


def resolve_inline_states(sm):
    counter = 1
    did_inline = True
    inlined = set()
    while did_inline:
        did_inline = False
        for state, trans in sm.all_transitions():
            if trans.inline_dest_state:
                new_parent = state.parent
                while new_parent in inlined:
                    new_parent = new_parent.parent
                new_parent.children.append(trans.dest_state)
                trans.dest_state.parent = new_parent
                trans.dest_state.name = trans.dest_state.name + 'Inline' + str(counter)
                trans.inline_dest_state = False
                counter += 1
                did_inline = True
                inlined.add(trans.dest_state)

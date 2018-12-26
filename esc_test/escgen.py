import state_machine
import parser

import itertools
import os
import sys
import tempfile

from collections import namedtuple

from args import EscArgumentParser


def make_enum_str(enum_prefix, state_names):
    enum_values = ['Undefined'] + state_names[1:]
    strs = []
    for i, value in enumerate(enum_values):
        strs.append('    ' + enum_prefix + '_' + value + ' = ' + str(i))
    return ',\n'.join(strs) + '\n'


def upper_case(name):
    result = ''
    for i, c in enumerate(name):
        if c.isupper() and i > 0 and name[i-1].islower():
            result = result + '_'
        result = result + c.upper()
    return result


def make_fndecl_str(sm, code):
    ret = '#define '
    sm_name = sm.prefix_name
    if sm.parent_file.namespace:
        sm_name = sm.parent_file.namespace.replace('::', '_') + '_' + sm_name
    ret += upper_case(sm_name) + '_SM_FUNCTION_DECLARATIONS \\\n'
    def decorate(decl):
        return '    ' + decl + ' \\\n' if decl else ''
    ret += 'public: \\\n'
    declarations = []
    declarations.extend(fn.output_declaration() for fn in code.triggered_op_fns)
    ret += ''.join(decorate(d) for d in declarations)
    ret += 'private: \\\n'
    declarations = []
    declarations.extend(fn.output_declaration() for fn in code.process_event_fns + code.handle_event_fns + code.entry_fns + code.exit_fns + code.is_in_fns)
    ret += ''.join(decorate(d) for d in declarations)
    if get_timer_events(sm.parent_file):
        ret += '    const char* getTimerEventName(const esc::EventId& eventId) const; \\\n'
    ret += '    const char* getSmName() const; \\\n'
    ret += '    int getStatechartSize(); \\\n'
    ret += '    void getStatechartStates(int stateVector[]); \\\n'
    ret += 'protected: \\\n'
    ret += '    void startBehavior(); \\\n'
    ret += '    bool handleEvent(esc::Event& ev); \\\n'
    return ret


def get_timer_events(sm_file):
    timer_states = unique([s for sm in sm_file.state_machines for s in state_machine.walk_states(sm.root_state) if s.needs_timer])
    return [state_machine.TimerEvent(s, [], 0) for s in timer_states]


def get_events(sm_file):
    timer_events = get_timer_events(sm_file)
    return [state_machine.Event('evNull')] + sm_file.events + sm_file.triggered_ops + timer_events


def get_eventid_define(event):
    ret = 'ESC'
    ret += '_' + event.event_name
    if event.namespace:
        ret += '_' + event.namespace.replace('::', '_')
    ret += '_eventId'
    return ret


def make_event_define_str(sm_file):
    import hashlib
    ret = ''
    for event in get_events(sm_file):
        if event.event_name == 'evNull':
            lower = higher = 0
        elif event.event_name.startswith('evTimer'):
            digest = hashlib.md5(event.event_name).hexdigest()
            int_digest = int(digest, 16)
            lower = int_digest % 2**64
            higher = (int_digest - lower) >> 64
        else:
            digest = hashlib.md5(event.event_name + str(event.namespace)).hexdigest()
            int_digest = int(digest, 16)
            lower = int_digest % 2**64
            higher = (int_digest - lower) >> 64
        params = ', '.join([str(i) + 'ULL' for i in higher, lower])
        ret += '#define ' + get_eventid_define(event) + ' ' + 'esc::EventId(' + params + ')\n'
    return ret


def make_event_decl_str(sm_file, event):
    ret = ''
    ret += 'class %s : public esc::Event {\n' % event.qualified_name
    ret += 'public:\n'
    members = []
    for param in event.params:
        members.append('%s %s' % (param.type, param.name))
    member_defs = ''
    if members:
        member_defs = '\n    ' + ';\n    '.join(members) + ';\n'
    def param_to_str(p):
        ret = p.type + ' ' + p.name
        if p.default:
            ret += ' = ' + p.default
        return ret
    args = ', '.join([param_to_str(p) for p in event.params])
    ret += '    %s(%s);\n' % (event.qualified_name, args)
    if any(p.delete for p in event.params):
        ret += '    ~%s();\n' % event.qualified_name
    ret += member_defs;
    ret += '};\n'
    return ret


def make_event_constructor_str(sm_file, event):
    ret = ''
    initializers = ['esc::Event(%s, %s)' % (get_eventid_define(event), '"' + event.qualified_name + '"')]
    members = []
    for param in event.params:
        initializers.append('%s(%s)' % (param.name, param.name))
        members.append('%s %s' % (param.type, param.name))
    args = ', '.join(members)
    ret += '    %s::%s(%s)\n' % (event.qualified_name, event.qualified_name, args)
    ret += '    : %s\n' % (', '.join(initializers))
    ret += '    {\n'
    ret += '    }\n'
    return ret


def make_event_destructor_str(sm_file, event):
    ret = ''
    if any(p.delete for p in event.params):
        ret += '    %s::~%s()\n' % (event.qualified_name, event.qualified_name)
        ret += '    {\n'
        for p in event.params:
            if p.delete:
                ret += '        delete %s;\n' % p.name
        ret += '    }\n\n'
    return ret


def unique(lst):
    ret = []
    for elem in lst:
        if elem not in ret:
            ret.append(elem)
    return ret


def get_roots(sm):
    return [sm.root_state] + list(find_regions(sm.root_state))


def generate_header_str(sm_file, codes):
    define_name = sm_file.name
    define_name = sm_file.namespace.replace('::', '_') + '_' + define_name if sm_file.namespace else define_name
    ret = '#ifndef %s_gen_H\n#define %s_gen_H\n\n\n' % (define_name, define_name)
    includes = ['"Esc.h"'] + sm_file.h_includes# + [e.replace('.esc', '.h') for e in sm_file.esc_includes]
    ret += '\n'.join(['#include ' + i for i in includes])
    ret += '\n\n'

    if sm_file.namespace:
        for nscomp in sm_file.namespace.split('::'):
            ret += 'namespace %s {\n\n' % nscomp
#    ret += 'namespace %s_gen {\n\n' % sm_file.name

    ret += make_event_define_str(sm_file) + '\n'
    ret += '\n'.join(make_event_decl_str(sm_file, event) for event in (sm_file.events + sm_file.triggered_ops)) + '\n\n'
    for sm, code in zip(sm_file.state_machines, codes):
        states = list(state_machine.walk_states(sm.root_state))
        state_names = [s.name for s in states]
        ret += 'enum %sState {\n%s};\n' % (sm.prefix_name, make_enum_str(sm.prefix_name, state_names)) + '\n'
        ret += 'class %sSmData {\n' % sm.prefix_name
        ret += 'public:\n'
        active_states = [s.name + '_active' for s in get_roots(sm)]
        history_states = [s.name + '_lastState' for s in state_machine.walk_states(sm.root_state) if has_history_variable(s)]
        states = active_states + history_states
        ret += '    %sSmData() : ' % sm.prefix_name + ', '.join([state + '(' + sm.prefix_name + '_Undefined)' for state in states]) + ' {}\n'
        for state in states:
            ret += '    %sState %s;\n' % (sm.prefix_name, state)
        ret += '};\n\n'
        ret += make_fndecl_str(sm, code) + '\n'

#    ret += '}\n\n'
    if sm_file.namespace:
        for nscomp in sm_file.namespace.split('::'):
            ret += '}\n\n'

    ret += '\n#endif\n'
    return ret


def indent_string(code_str, indent_str):
    lines = code_str.split('\n')
    if lines[-1] == '':
        del lines[-1]
    lines = [indent_str + line for line in lines]
    return '\n'.join(lines) + '\n'


def enclose_in_brackets(code_str):
    lines = code_str.split('\n')
    if lines[-1] == '':
        del lines[-1]
    lines = ['    ' + line for line in lines]
    lines = ['{'] + lines + ['}']
    return '\n'.join(lines) + '\n'


def cpp_state_name(state):
    return state.sm.prefix_name + '_' + state.name


class Code(object):
    def __init__(self, sm):
        self.sm = sm
        self.process_event_fns = []
        self.handle_event_fns = []
        self.entry_fns = []
        self.exit_fns = []
        self.triggered_op_fns = []
        self.is_in_fns = []


class ProcessEventFn(namedtuple('ProcessEventFn', ['state', 'cases', 'parent_root_state'])):
    def output_declaration(self):
        return 'bool %s_processEvent(esc::Event& ev);' % self.state.name

    def output(self):
        ret = 'bool %s::%s_processEvent(esc::Event& ev)\n{\n' % (self.state.sm.full_cpp_class_name, self.state.name)
        ret += '    bool consumed = false;\n'
        if not self.cases:
            ret += '    static_cast<void>(ev);\n'
        ret += '\n'
        ret += '    switch (smData_.%s_active) {\n' % self.parent_root_state.name
        for case in self.cases:
            ret += '        case %s:\n' % (self.state.sm.prefix_name + '_' + case.state.name)
            ret += '            consumed = %s(ev);\n' % case.handle_event_fn_name
            ret += '            break;\n\n'
        ret += '        default:\n'
        ret += '            break;\n'
        ret += '    }\n'
        ret += '\n'
        ret += '    return consumed;\n'
        ret += '}\n'
        return ret

ProcessEventFnCase = namedtuple('ProcessEventFnCase', ['state', 'handle_event_fn_name'])


class ProcessEventRegionRootFn(namedtuple('ProcessEventRegionRootFn', ['state', 'parent_root_state', 'handle_event_fn_name'])):
    def output_declaration(self):
        return 'bool %s_processEvent(esc::Event& ev);' % self.state.name

    def output(self):
        ret = 'bool %s::%s_processEvent(esc::Event& ev)\n{\n' % (self.state.sm.full_cpp_class_name, self.state.name)
        ret += '    bool consumed = false;\n'
        ret += '\n'

        for region in self.state.children:
            ret += '    if (%s_processEvent(ev) == true) {\n' % region.name
            ret += '        consumed = true;\n'
            ret += '        if (smData_.%s_active != %s) {\n' % (self.parent_root_state.name, cpp_state_name(self.state))
            ret += '            return consumed;\n'
            ret += '        }\n'
            ret += '    }\n'
            ret += '\n'

        if self.handle_event_fn_name:
            ret += '    if (!consumed) {\n'
            ret += '        consumed = %s(ev);\n' % self.handle_event_fn_name
            ret += '    }\n'
            ret += '\n'

        ret += '    return consumed;\n'
        ret += '}\n'
        return ret


class HandleEventFn(namedtuple('HandleEventFn', ['name', 'state', 'cases', 'parent_fn'])):
    def output_declaration(self):
        return 'bool %s_handleEvent(esc::Event& ev);' % self.state.name

    def output(self):
        ret = 'bool %s::%s_handleEvent(esc::Event& ev)\n{\n' % (self.state.sm.full_cpp_class_name, self.state.name)
        ret += '    bool consumed = false;\n'
        ret += '\n'

        for case in self.cases:
            ret += case.output(self.state.sm, is_first=(case is self.cases[0]))

        if self.parent_fn:
            ret += '\n'
            ret += '    if (!consumed) {\n'
            ret += '        consumed = %s(ev);\n' % self.parent_fn
            ret += '    }\n'

        ret += '\n    return consumed;\n'
        ret += '}\n'
        return ret


class HandleEventFnCase(namedtuple('HandleEventFnCase', ['event', 'statement'])):
    def output(self, sm, is_first):
        ret = '    '
        if not is_first:
            ret += 'else '
        ret += 'if (ev.getId() == %s) {\n' % get_eventid_define(self.event)
        if self.event.params:
            full_name = self.event.qualified_name
            if self.event.namespace:
                full_name = self.event.namespace + '::' + full_name
            ret += '        {0}* params = static_cast<{0}*>(&ev);\n'.format(full_name)
        ret += '\n'

        ret += indent_string(self.statement.output(is_default_transition=False), '        ')

        ret += '    }\n'
        return ret


class IfStatement(namedtuple('IfStatement', ['expression', 'if_clause', 'else_clause'])):
    def output(self, is_default_transition):
        ret = 'if (%s) ' % self.expression + enclose_in_brackets(self.if_clause.output(is_default_transition))
        if self.else_clause:
            ret += 'else ' + enclose_in_brackets(self.else_clause.output(is_default_transition))
        return ret


class StatementList(namedtuple('StatementList', ['statements'])):
    def output(self, is_default_transition):
        ret = ''
        for stmt in self.statements:
            ret += stmt.output(is_default_transition)
        return ret


class CompleteTransition(namedtuple('CompleteTransition', ['code', 'source', 'actions', 'dest', 'use_history'])):
    def output(self, is_default_transition):

        if self.dest:
            # the common state is never exited/entered
            common_state = state_machine.calc_common_state(self.source, self.dest)
            # if this is a transition into a child state, it is currently always considered an external transition (i.e. it exists and then enters the source state)
            if self.source is common_state and not is_default_transition:
                if not self.dest.is_choice: # exception: if the transition is to a condition point, it is considered a local transition, according to Rhapsody
                    common_state = common_state.parent

            if not is_default_transition:
                # the exit state is the state just below the common state in the chain
                exit_state = None
                exit_fn = None
                exit_states = list(state_machine.get_parent_chain(self.source, common_state))
                if exit_states:
                    exit_state = exit_states[-1]
                    if not exit_state.is_choice:
                        exit_fn = get_exit_function(self.code, exit_state)

            entry_states = list(reversed(list(state_machine.get_parent_chain(self.dest, common_state))))
            # basic entry states are all the ones that are entered, except the destination state
            basic_entry_states = entry_states[:-1]

            # the entry function for the dest state (will do basic entry + call child function entry functions and handle default transititions)
            if self.use_history:
                entry_fn = next((fn for fn in self.code.entry_fns if fn.state == self.dest and isinstance(fn, EntryHistoryFn)), None)
            else:
                entry_fn = next((fn for fn in self.code.entry_fns if fn.state == self.dest and isinstance(fn, EntryFn)), None)
            assert entry_fn or self.dest.is_choice

        ret = ''

        def add_destroyed_check():
            ret = ''
            if not is_default_transition:
                ret += 'if (!ev.isEnabled())\n'
                ret += '{\n'
                ret += '    throw esc::SmDestroyedException();\n'
                ret += '}\n'
            return ret


        if self.dest:
            if not is_default_transition and exit_state and not exit_state.is_choice:
                if not exit_fn.is_empty():
                    exit_fn_name = make_exit_fn_name(exit_state)
                    ret += '%s();\n' % exit_fn_name
                else:
                    ret += '// ' + exit_state.name + ' exit'
                ret += '\n'

        for action in self.actions:
            ret += '/// Transition action (from esc line ' + str(action.file_pos.line) + ')\n'
            ret += action.code + '\n'
            ret += add_destroyed_check()
            ret += '\n'

        if self.dest:
            ret += '/// Entry handling\n'
            fragments = []
            for state in basic_entry_states:
                # enter other regions
                if state.parent in basic_entry_states and state.parent.is_region_root:
                    for other_region in state.parent.children:
                        if other_region is not state:
                            fragments.append(ArbitraryCodeFragment('%s();\n' % make_entry_fn_name(self.code, other_region, False)))
                fragments.extend(common_entry(state, find_parent_root_state(state)))
            ret += output_fragments(optimize_fragments(fragments))

            if entry_fn:
                ret += '/// ' + self.dest.name + ' entry\n'
                ret += '{\n'
                ret += entry_fn.output_body()
                ret += '}\n'
                ret += add_destroyed_check()
                ret += '\n'

        if not is_default_transition:
            ret += 'consumed = true;\n'

        return ret


class ArbitraryCodeFragment(namedtuple('ArbitraryCodeFragment', ['code_fragment_str'])):
    def output(self):
        return self.code_fragment_str


class SetActiveStatement(namedtuple('SetActiveStatement', ['indent', 'parent_root_state', 'state'])):
    def output(self):
        return self.indent + 'smData_.%s_active = %s;\n' % (self.parent_root_state.name, cpp_state_name(self.state))


def output_fragments(fragments):
    return ''.join(frag.output() for frag in fragments)


def optimize_fragments(fragments):
    "Avoids outputting multiple adjacent statements setting the same variable (wihout reading it inbetween)"
    result = []
    for fragment in fragments:
        if result and isinstance(result[-1], SetActiveStatement) and isinstance(fragment, SetActiveStatement):
            if fragment.parent_root_state == result[-1].parent_root_state:
                del result[-1]
        result.append(fragment)
    return result


def common_entry(state, parent_root_state, ind=''):
    fragments = []
    if state.parent:
        fragments.append(SetActiveStatement(ind, parent_root_state, state))
    code = ''
    if state.entry_action:
        code += ind + '/// Entry action (from esc line ' + str(state.entry_action.file_pos.line) + ')\n'
        code += '{\n'
        code += indent_string(state.entry_action.code, ind)
        code += '}\n'
    if state.has_timer_event:
        code += ind + 'scheduleTimer(%s, %s);\n' % (get_eventid_define(state_machine.TimerEvent(state.parent, [], 0)), state.timer_event.timeout)
    if state.has_null_transition:
        code += ind + 'pushNullTransition();\n'
    if code:
        fragments.append(ArbitraryCodeFragment(code))
    return fragments


class EntryFn(object):
    def __init__(self, code, state, parent_root_state):
        self.code = code
        self.state = state
        self.parent_root_state = parent_root_state
        self.is_referenced = False

    def output_declaration(self):
        if not self.is_referenced:
            return ''
        return 'void %s();' % make_entry_fn_name(self.code, self.state, False)

    def output_body(self, indent=''):
        ret = output_fragments(common_entry(self.state, self.parent_root_state, ind=indent))
        if self.state.is_region_root:
            for region in self.state.children:
                ret += indent + '%s();\n' % make_entry_fn_name(self.code, region, False)
        elif self.state.default_transition:
            stm = make_transition_statement(self.code, self.state, [self.state.default_transition])
            ret += indent_string(stm.output(is_default_transition=True), indent)
        return ret

    def output(self):
        if not self.is_referenced:
            return ''
        ret = 'void %s::%s()\n{\n' % (self.state.sm.full_cpp_class_name, make_entry_fn_name(self.code, self.state, False))
        ret += self.output_body('    ')
        ret += '}\n'
        return ret


class EntryHistoryFn(object):
    def __init__(self, code, state, parent_root_state):
        self.code = code
        self.state = state
        self.parent_root_state = parent_root_state
        self.is_referenced = False

    def output_declaration(self):
        if not self.is_referenced:
            return ''
        return 'void %s();' % make_entry_fn_name(self.code, self.state, True)

    def output_body(self, indent=''):
        ret = output_fragments(common_entry(self.state, self.parent_root_state, ind=indent))
        if self.state.children:
            if not self.state.is_region_root:
                assert has_history_variable(self.state)
                ret += indent + 'if (smData_.%s_lastState != %s_Undefined) {\n' % (self.state.name, self.state.sm.prefix_name)
                ret += indent + '    switch (smData_.%s_lastState) {\n' % self.state.name
                for sub_state in find_active_states(self.state):
                    ret += indent + '        case %s_%s:\n' % (self.state.sm.prefix_name, sub_state.name)
                    ret += indent + '        {\n'
                    ret += indent + '            %s();\n' % make_entry_fn_name(self.code, sub_state, True)
                    ret += indent + '        }\n'
                    ret += indent + '        break;\n'
                ret += indent + '        default:\n'
                ret += indent + '            break;\n'
                ret += indent + '    }\n'
                ret += indent + '}\n'
            else:
                for region in self.state.children:
                    ret += indent + '%s();\n' % make_entry_fn_name(self.code, region, True)
        return ret

    def output(self):
        if not self.is_referenced:
            return ''
        ret = 'void %s::%s()\n{\n' % (self.state.sm.full_cpp_class_name, make_entry_fn_name(self.code, self.state, True))
        ret += self.output_body('    ')
        ret += '}\n'
        return ret


class ExitFn(namedtuple('ExitFn', ['code', 'state', 'parent_root_state', 'parent_history_state'])):
    def output_declaration(self):
        if not self.is_empty():
            return 'void %s();' % make_exit_fn_name(self.state)
        else:
            return ''

    def output_body(self):
        ret = ''
        if self.state.is_region_root:
            for region in self.state.children:
                ret += '    %s();\n' % make_exit_fn_name(region)
        elif self.state.sub_states:
            switch_sub_states = [s for s in self.state.sub_states if not get_exit_function(self.code, s).is_empty()]
            if switch_sub_states:
                ret += '    switch (smData_.%s_active) {\n' % self.parent_root_state.name
                for sub_state in switch_sub_states:
                    for active_state in find_active_states(sub_state):
                        ret += '    case %s:\n' % cpp_state_name(active_state)
                    ret += '        %s();\n' % make_exit_fn_name(sub_state)
                    ret += '        break;\n'
                ret += '    default:\n'
                ret += '        break;\n'
                ret += '    }\n'
        parent = self.state.parent
        if not parent.parent: # root state
            parent_str = self.state.sm.prefix_name + '_Undefined'
        else:
            parent_str = cpp_state_name(parent)
        ret += '    smData_.%s_active = %s;\n' % (self.parent_root_state.name, parent_str)
        if self.parent_history_state:
            ret += '    smData_.%s_lastState = %s;\n' % (self.parent_history_state.name, cpp_state_name(self.state))
        if self.state.exit_action:
            ret += '    /// Exit action (from esc line ' + str(self.state.exit_action.file_pos.line) + ')\n'
            ret += '    %s\n' % self.state.exit_action.code
        if self.state.has_null_transition:
            ret += '        popNullTransition();\n'
        if self.state.has_timer_event:
            ret += '    cancelTimer(%s);\n' % (get_eventid_define(state_machine.TimerEvent(self.state.parent, [], 0)))
        return ret

    def is_empty(self):
        is_empty = self.output_body() == ''
        return is_empty

    def output(self):
        ret = ''
        if not self.is_empty():
            ret += 'void %s::%s()\n{\n' % (self.state.sm.full_cpp_class_name, make_exit_fn_name(self.state))
            ret += self.output_body()
            ret += '}\n'
        return ret


class TriggeredOpFn(namedtuple('TriggeredOpFn', ['sm', 'triggered_op_event'])):
    def arg_string(self):
        return ', '.join([p.type + ' ' + p.name for p in self.triggered_op_event.params])

    def output_declaration(self):
        return 'void %s(%s);' % (self.triggered_op_event.name, self.arg_string())

    def output(self):
        ret = 'void %s::%s(%s)\n{\n' % (self.sm.full_cpp_class_name, self.triggered_op_event.name, self.arg_string())
        arg_str = ', '.join([p.name for p in self.triggered_op_event.params])
        if arg_str:
            arg_str = '(' + arg_str + ')'
        ret += '    %s triggerEvent%s;\n' % (self.triggered_op_event.qualified_name, arg_str)
        ret += '    processEvent(triggerEvent);\n'
        ret += '}\n'
        return ret


class IsInFn(namedtuple('IsInFn', ['state', 'parent_root_state', 'active_states', 'sm'])):
    def output_declaration(self):
        return 'bool %s_IN() const;' % self.state.name

    def output(self):
        ret = 'bool %s::%s_IN() const {\n' % (self.sm.full_cpp_class_name, self.state.name)
        cond = ' || '.join(['smData_.%s_active == %s' % (self.parent_root_state.name, cpp_state_name(state)) for state in self.active_states])
        ret += '    return %s;\n' % cond
        ret += '}\n'
        return ret


def indent(indent_str, s):
    lines = s.split('\n')
    lines = [indent_str + line for line in lines]
    return '\n'.join(lines)


def make_entry_fn_name(code, state, history):
    if not history or not state.children:
        [fn for fn in code.entry_fns if fn.state is state and isinstance(fn, EntryFn)][0].is_referenced = True
        return state.name + '_enter'
    else:
        [fn for fn in code.entry_fns if fn.state is state and isinstance(fn, EntryHistoryFn)][0].is_referenced = True
        return state.name + '_enterHistory'


def get_exit_function(code, state):
    fn = [fn for fn in code.exit_fns if fn.state is state][0]
    return fn


def make_exit_fn_name(state):
    return state.name + '_exit'


Segment = namedtuple('Segment', ['code', 'source', 'transition', 'next_segments'])
Step = namedtuple('Step', ['segments', 'next_steps'])
TransitionCase = namedtuple('TransitionCase', ['guards', 'transition', 'sub_cases'])


def make_segment(code, source, transition, level=1):
    dest = transition.dest_state
    if dest and (dest.is_junction or dest.is_diagram_connector or dest.is_choice or dest.is_join):
        if dest.is_diagram_connector:
            if dest.transitions:
                assert len(dest.transitions) == 1
                next_transitions = [dest.transitions[0]]
            else:
                new_dest = find_connector(code.sm, dest.name)
                next_transitions = [state_machine.Transition(None, new_dest, None, None, None)]
        else:
            next_transitions = dest.transitions
        next_segments = [make_segment(code, dest, trans, level + 1) for trans in next_transitions]
        return Segment(code, source, transition, next_segments)
    else:
        return Segment(code, source, transition, [])


def make_steps(segment):
    if not segment.next_segments:
        return [Step([segment], [])]
    new_segment = Segment(segment.code, segment.source, segment.transition, [])
    next_steps = concat([make_steps(next_segment) for next_segment in segment.next_segments])
    if segment.transition.dest_state.is_choice:
        return [Step([new_segment], next_steps)]
    else:
        return [Step([new_segment] + next_step.segments, next_step.next_steps) for next_step in next_steps]


def make_transition_case(code, step):
    guards = [segment.transition.guard for segment in step.segments if segment.transition.guard]
    actions = [segment.transition.action for segment in step.segments if segment.transition.action]
    complete_transition = CompleteTransition(code, step.segments[0].source, actions,
                                             step.segments[-1].transition.dest_state, step.segments[-1].transition.use_history)
    sub_cases = [make_transition_case(code, next_step) for next_step in step.next_steps]
    return TransitionCase(guards, complete_transition, sub_cases)


def combine_transition_cases(cases):
    def make_if_stmt(guards, if_clause, else_clause):
        return IfStatement(' && '.join(['(' + guard.code  + ')' for guard in guards]), if_clause, else_clause)

    cases = [c for c in cases if c.guards] + [c for c in cases if not c.guards] # put non-guard as final else case
    stmt = StatementList([cases[-1].transition])
    if cases[-1].sub_cases:
        stmt.statements.append(combine_transition_cases(cases[-1].sub_cases))
    if cases[-1].guards:
        stmt = make_if_stmt(cases[-1].guards, stmt, None)
    for case in reversed(cases[:-1]):
        case_stmt = StatementList([case.transition])
        if case.sub_cases:
            case_stmt.statements.append(combine_transition_cases(case.sub_cases))
        stmt = make_if_stmt(case.guards, case_stmt, stmt)
    return stmt


def make_transition_statement(code, state, transitions):
    segments = [make_segment(code, state, trans) for trans in transitions]
    steps = concat([make_steps(segment) for segment in segments])
    cases = [make_transition_case(code, step) for step in steps]
    combined = combine_transition_cases(cases)
    return combined


def add_join_guard(sm, state, statement):
    join = state.outgoing_transitions[0].dest_state
    other_src_states = [s for s in state_machine.walk_states(sm.root_state, include_all=True) if s.is_join_src_state and s.outgoing_transitions[0].dest_state is join and not s is state]
    guard = ' && '.join('smData_.' + find_parent_root_state(s).name + '_active == ' + sm.prefix_name + '_' + s.name for s in other_src_states)
    assert guard
    return IfStatement(guard, statement, None)


def make_handle_event_fn(sm, state, code):
    if state.parent and state.parent.name != 'RootState' and not state.parent.is_region:
        parent_fn_name = get_handle_event_fn(sm, state.parent, code)
    else:
        parent_fn_name = None

    if not state.transitions and not parent_fn_name:
        return None

    event_fn_cases = []
    all_transitions = sorted([t for t in state.transitions if not isinstance(t.event, state_machine.Default)], key=lambda t: t.event.event_name if t.event else '')
    for event, event_transitions in itertools.groupby(all_transitions, lambda t: t.event):
        event_transitions = list(event_transitions)
        combined = make_transition_statement(code, state, event_transitions)

        if not event:
            event = state_machine.NullEvent
        if state.is_join_src_state and event_transitions[0].dest_state: # not for internal events
            combined = add_join_guard(sm, state, combined)
        event_fn_cases.append(HandleEventFnCase(event, combined))

    fn = HandleEventFn(state.name + '_handleEvent',
                       state,
                       event_fn_cases,
                       parent_fn_name)
    return fn


def get_handle_event_fn(sm, state, code):
    for handle_event_fn in code.handle_event_fns:
        if handle_event_fn.state == state:
            return handle_event_fn.name

    new_handle_event_fn = make_handle_event_fn(sm, state, code)
    if new_handle_event_fn:
        code.handle_event_fns.append(new_handle_event_fn)
        return new_handle_event_fn.name
    else:
        return None


def make_process_event_fn(sm, state, code):
    active = find_active_states(state)
    cases = []
    for sub in active:
        if sub.is_region_root:
            event_fn_name = sub.name + '_processEvent'
        else:
            event_fn_name = get_handle_event_fn(sm, sub, code)
        if event_fn_name:
            cases.append(ProcessEventFnCase(sub, event_fn_name))
    parent_root_state = find_parent_root_state(state)
    return ProcessEventFn(state, cases, parent_root_state)


def find_parent_root_state(state):
    if not state.parent or state.is_region:
        return state
    else:
        return find_parent_root_state(state.parent)


def find_parent_history_state(state):
    if not state.needs_history:
        return None
    if not is_active(state):
        return None
    state = state.parent
    while state and not has_history_variable(state):
        state = state.parent
    return state


def has_history_variable(state):
    if state.is_region_root: # region roots don't need history variables, the EntryHistory function just call the child's EnterHistory functions
        return False
    elif state.has_history_state: # otherwise, if the state has its own history state, it always needs a history variable
        return True
    else: # finally, if a parent has a history state, this state needs a variable if it is a region
        return state.needs_history and state.is_region


def make_process_event_region_root_fn(sm, state, code):
    parent_root_state = find_parent_root_state(state)
    handle_event_fn_name = get_handle_event_fn(sm, state, code)
    return ProcessEventRegionRootFn(state, parent_root_state, handle_event_fn_name)


def find_active_states(state):
    if not state.sub_states:
        yield state
    else:
        for child in state.sub_states:
            for child_active in find_active_states(child):
                yield child_active


def is_active(state):
    return state in find_active_states(state)


def find_region_roots(state):
    return [s for s in state_machine.walk_states(state) if s.is_region_root]


def find_regions(state):
    return [s for s in state_machine.walk_states(state) if s.is_region]


def generate_implementation_str(sm_file, codes):
    ret = ''
#    ret += '\n'.join(['#include ' + i for i in sm_file.cpp_includes + ['"' + sm_file.name + '.gen.h"']])
    ret += '\n'.join(['#include ' + i for i in sm_file.cpp_includes])
    ret += '\n\n'

    if sm_file.namespace:
        for nscomp in sm_file.namespace.split('::'):
            ret += 'namespace %s {\n\n' % nscomp

    ret += '\n'.join(make_event_constructor_str(sm_file, event) for event in (sm_file.events + sm_file.triggered_ops)) + '\n\n'
    ret += ''.join(make_event_destructor_str(sm_file, event) for event in (sm_file.events + sm_file.triggered_ops)) + '\n\n'

    for sm, code in zip(sm_file.state_machines, codes):
        ret += '\n'.join([fn.output() for fn in code.process_event_fns]) + '\n'
        ret += '\n'.join([fn.output() for fn in code.handle_event_fns]) + '\n'
        ret += '\n'.join([fn.output() for fn in code.triggered_op_fns]) + '\n'

        ret += '\n'.join(o for o in [fn.output() for fn in code.entry_fns + code.exit_fns] if o) + '\n'

        ret += '\n'.join([fn.output() for fn in code.is_in_fns]) + '\n'

        handle_event = 'bool %s::handleEvent(esc::Event& ev)\n{\n' % sm.full_cpp_class_name + \
            '    return RootState_processEvent(ev);\n}\n'
        ret += handle_event + '\n'

        timer_events = get_timer_events(sm_file)
        if timer_events:
            get_event_name = 'const char* %s::getTimerEventName(const esc::EventId& eventId) const\n{\n' % sm.full_cpp_class_name
            first = True
            for event in timer_events:
                else_str = 'else ' if not first else ''
                get_event_name += '    ' + else_str + 'if (eventId == ' + get_eventid_define(event) + ') {\n'
                get_event_name += '        return "' + event.event_name + '";\n'
                get_event_name += '    }\n'
            get_event_name += '    assert(false);\n'
            get_event_name += '}\n'
            ret += get_event_name + '\n'

        start_behavior = 'void %s::startBehavior()\n{\n    %s();\n    completeStartBehavior();\n}\n' % (sm.full_cpp_class_name, make_entry_fn_name(code, sm.root_state, False))
        ret += start_behavior + '\n'

        get_sm_name = 'const char* %s::getSmName() const\n{\n' % sm.full_cpp_class_name
        get_sm_name += '    return "%s";\n}\n' % sm.full_cpp_class_name
        ret += get_sm_name + '\n'

        num_timers = len([s for s in state_machine.walk_states(sm.root_state) if s.needs_timer])

        roots = get_roots(sm)

        get_statechart_size = 'int %s::getStatechartSize()\n{\n    return %s;\n}\n' % (sm.full_cpp_class_name, len(roots))
        ret += get_statechart_size + '\n'

        get_statechart_states = 'void %s::getStatechartStates(int stateVector[])\n{\n' % sm.full_cpp_class_name + \
            ''.join(['    stateVector[%s] = smData_.%s_active;\n' % (i, state.name) for i, state in enumerate(roots)]) + '}\n'
        ret += get_statechart_states + '\n'

    if sm_file.namespace:
        for nscomp in sm_file.namespace.split('::'):
            ret += '}\n\n'

    return ret


def find_child(state, fn):
    for child in state.children:
        if fn(child):
            return child


def find_outer_entry_connector(state, name):
    return find_child(state, lambda c: c.is_entry_connector and c.name == name)


def find_outer_exit_connector(state, name):
    return find_child(state, lambda c: c.is_exit_connector and c.name == name)


def walk_transitions(state):
    for t in state.transitions:
        yield t
        if t.inline_dest_state:
            for tt in walk_transitions(t.dest_state):
                yield tt
    for c in state.children:
        for tt in walk_transitions(c):
            yield tt


def find_containing_region(state, regions):

    # this is in order to allow inline states when there is only a single region
    #(then we can not look at the state parents to find the region, but we do not need to anyway
    if len(regions) == 1:
        return regions[0]

    if state in regions:
        return state
    else:
        return find_containing_region(state.parent, regions)


def find_referencing_regions(state, regions):
    def is_referencing(region):
        return any(trans for trans in walk_transitions(region) if trans.dest_state is state)
    return [r for r in regions if is_referencing(r)]


def make_helper_state(conn, number=None):
    number_str = str(number) if number is not None else ''
    helper = state_machine.State(conn.parent.name + '_' + conn.name + '_Helper' + number_str, None, [], None, None)
    helper.transitions = conn.transitions
    return helper


def redirect_transitions(state, source, dest):
    for t in walk_transitions(state):
        if t.dest_state is source:
            t.dest_state = dest


def get_root_state(state):
    if state.parent:
        return get_root_state(state.parent)
    else:
        return state


def merge_sub_statecharts(sm_file):
    for sub_sm in [sm for sm in sm_file.state_machines if sm.is_sub_sm]:
        source_states = [s for s in sm_file.get_states(sub_sm.name) if s.parent]
        assert len(source_states) == 1
        source_state = source_states[0]
        dest_state = sub_sm.root_state

        dest_children = [c for c in dest_state.children if not (c.is_entry_connector or c.is_exit_connector)]
        if dest_state.is_region_root:
            regions = dest_children
        else:
            regions = [state_machine.State("<fake-region>", None, dest_children, None, None)]
        entry_connectors = [c for c in dest_state.children if c.is_entry_connector]
        exit_connectors = [c for c in dest_state.children if c.is_exit_connector]

        for entry_conn in entry_connectors:
            outer_entry_conn = find_outer_entry_connector(source_state, entry_conn.name)
            entry_conn_region = find_containing_region(entry_conn.transitions[0].dest_state, regions)
            helper_state = make_helper_state(entry_conn)
            entry_conn_region.add_child(helper_state)
            redirect_transitions(get_root_state(source_state), outer_entry_conn, helper_state)

        for exit_conn in exit_connectors:
            outer_exit_conn = find_outer_exit_connector(source_state, exit_conn.name)
            for i, exit_conn_region in enumerate(find_referencing_regions(exit_conn, regions)):
                helper_state = make_helper_state(outer_exit_conn, i + 1)
                exit_conn_region.add_child(helper_state)
                redirect_transitions(exit_conn_region, exit_conn, helper_state)

        if dest_state.is_region_root:
            source_state.set_children(regions)
        else:
            source_state.set_children(regions[0].children)
        source_state.transitions.extend(dest_state.transitions)
        redirect_transitions(dest_state, dest_state, source_state)
        if dest_state.has_history_state:
            source_state.has_history_state = True

    sm_file.state_machines = [sm for sm in sm_file.state_machines if not sm.is_sub_sm]


def prefix_duplicate_names(sm):
    name_states = {}
    for name, states in itertools.groupby(sorted(state_machine.walk_states(sm.root_state),
                                                 key=lambda st: st.name), key=lambda st: st.name):
        name_states[name] = list(states)

    changes = []
    for name, states in name_states.items():
        if len(states) > 1:
            for state in states:
                changes.append((state, state.parent.name + '_' + state.name))

    for state, new_name in changes:
        state.name = new_name


def find_connector(sm, name):
    for state in state_machine.walk_states(sm.root_state, include_all=True):
        if state.name == name:
            assert len(state.transitions) == 1
            return state
    assert False


def get_sm_triggered_ops(sm):
    triggered_ops = [tg.name for tg in sm.parent_file.triggered_ops]
    sm_triggered_ops = []
    for _, trans in sm.all_transitions():
        if not trans.event:
            continue
        if trans.event.name in triggered_ops and trans.event.name not in [tg.name for tg in sm_triggered_ops]:
            sm_triggered_ops.append(trans.event)
    return sm_triggered_ops


def find_sub_states(state):
    if state.is_region:
        return
    yield state
    for child in state.sub_states:
        for child_active in find_sub_states(child):
            yield child_active


def generate_sm(sm, code):
    prefix_duplicate_names(sm)
    state_machine.resolve_inline_states(sm)

    roots = get_roots(sm)
    region_roots = list(find_region_roots(sm.root_state))
    code.process_event_fns = [make_process_event_fn(sm, root, code) for root in roots] + \
        [make_process_event_region_root_fn(sm, region_root, code) for region_root in region_roots]
    code.triggered_op_fns = [TriggeredOpFn(sm, tg) for tg in sm.parent_file.triggered_ops]

    for state in state_machine.walk_states(sm.root_state):
        parent_root_state = find_parent_root_state(state)

        code.entry_fns.append(EntryFn(code, state, parent_root_state))
        if state is sm.root_state:
            code.entry_fns[-1].is_referenced = True
        if has_history_variable(state) or (state.needs_history and state.is_region_root):
            code.entry_fns.append(EntryHistoryFn(code, state, parent_root_state))

        if state.name not in ['RootState']:
            code.exit_fns.append(ExitFn(code, state, parent_root_state, find_parent_history_state(state)))

        if state.parent and not state.is_region:
            active_states = find_sub_states(state)
            code.is_in_fns.append(IsInFn(state, parent_root_state, active_states, sm))

def atomic_write(path, content):
    output_dir, _ = os.path.split(path)
    fd, temp_path = tempfile.mkstemp("~","tmp",output_dir)
    os.write(fd, content)
    os.close(fd)
    os.rename(temp_path,path)


def parse_esc(base_path, esc_path):
    return parser.parse_file(base_path, esc_path)


def generate(sm_file, cpp_path, h_path):
    codes = []

    merge_sub_statecharts(sm_file)

    for sm in sm_file.state_machines:
        sm.root_state.name = 'RootState'
        code = Code(sm)
        generate_sm(sm, code)
        codes.append(code)

    implementation_str = generate_implementation_str(sm_file, codes)
    atomic_write(cpp_path,implementation_str)

    header_str = generate_header_str(sm_file, codes)
    atomic_write(h_path,header_str)


def calc_output_paths(esc_path, output_dir):
    input_dir, input_esc_file = os.path.split(esc_path)
    base, _ = os.path.splitext(input_esc_file)

    if not output_dir:
        output_dir = input_dir

    cpp_path = os.path.join(output_dir, base + '.gen.cpp')
    h_path = os.path.join(output_dir, base + '.gen.h')

    return cpp_path, h_path


def concat(lists):
    return list(itertools.chain.from_iterable(lists))


def parse_args():
    description = ('Generate .cpp and .h files from ESC Statechart '
                   'description (.esc) file.')
    arg_parser = EscArgumentParser(description=description)
    arg_parser.add_argument('-n', '--syntax-only', action='store_true',
                            help='Only check the syntax of the ESC file.')
    return arg_parser.parse_args()


def main():
    args = parse_args()
    if args.syntax_only:
        parse_esc(args.base_path, args.esc_file)
    else:
        sm_file = parse_esc(args.base_path, args.esc_file)
        cpp_path, h_path = calc_output_paths(args.esc_file, args.output_dir)
        generate(sm_file, cpp_path, h_path)


if __name__ == '__main__':
    try:
        main()
    except IOError, e:
        print(e.message)
        sys.exit(1)

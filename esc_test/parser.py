from parse_tree import Event, Param, State, Transition, Entry, Exit, Region, ParseError, FilePosition, CodeFragment
import parse_tree

import re
import os
import sys
from collections import namedtuple


class ParsedToken(object):
    def __init__(self, string, file_pos=None):
        self.string = string
        self.file_pos = file_pos


def parse_token(string):
    if string.startswith('tm['):
        count = 1
        index = 3
        while count > 0:
            if string[index] == '[':
                count += 1
            elif string[index] == ']':
                count -= 1
            index += 1
        return string[:index]
    elif string.startswith('['):
        return '['
    elif string.startswith('->'):
        return '->'
    else:
        tokens = re.split(r'(\[| |#|->)', string)
        return tokens[0]


def parse_parameter(param_str, orig_lineno):
    param_str = param_str.strip(' ')
    if param_str.startswith('<delete> '):
        delete = True
        param_str = param_str[len('<delete> '):]
    else:
        delete = False
    words = param_str.split()
    if len(words) < 2:
        raise ParseError(orig_lineno, 'syntax error, parameter must include both type and name')
    if words[-2] == '=':
        pname = words[-3]
        default_value = words[-1]
        ptype = ' '.join(words[:-3])
    else:
        pname = words[-1]
        default_value = None
        ptype = ' '.join(words[:-1])
    return Param(pname, ptype, default_value, delete)


def create_regions(state, stmt_before_region_list):
    regions = [[]]
    other_statements = []
    for stmt in state.statements:
        if (isinstance(stmt, parse_tree.StateT) and not stmt.state_type in ['entry connector', 'exit connector']) or (isinstance(stmt, parse_tree.TransitionT) and stmt.event_name == 'default'):
            regions[-1].append(stmt)
            if stmt in stmt_before_region_list:
                regions.append([])
            if isinstance(stmt, parse_tree.StateT):
                create_regions(stmt, stmt_before_region_list)
        else:
            other_statements.append(stmt)
    if len(regions) > 1:
        state.statements[:] = other_statements + [Region(region_stmts) for region_stmts in regions]


def is_single_cpp_statement(action):
    in_string_literal = False
    in_char_literal = False
    in_comment = False
    i = 0
    while i < len(action):
        ch = action[i]
        if in_string_literal:
            if action[i:i+2] == r'\"':
                i += 1
            elif ch == '"':
                in_string_literal = False
        elif in_char_literal:
            if action[i:i+2] == r'\'':
                i += 1
            elif ch == "'":
                in_char_literal = False
        elif in_comment:
            if action[i:i+2] == '*/':
                in_comment = False
        else:
            if ch == '"':
                in_string_literal = True
            elif ch == "'":
                in_char_literal = True
            elif action[i:i+2] == '/*':
                in_comment = True
            elif ch == ';':
                if i < len(action) - 1:
                    return False
        i += 1
    return True


class Declaration(object):
    def __init__(self, value):
        self.lineno = None
        self.value = value


class Parser(object):
    def __init__(self, path, esc_str):
        self.path = path
        self.lines = esc_str.split('\n')
        self.current_lineno = 1
        self.current_colno = 1
        self.current_indent = 0
        self.parsing_action = False

        self.h_includes = Declaration([])
        self.cpp_includes = Declaration([])
        self.esc_includes = Declaration([])
        self.events = Declaration([])
        self.triggered_operations = Declaration([])
        self.namespace = Declaration(None)
        self.state_machines = []

    def raise_error(self, error_string, lineno=None):
        if lineno is None:
            lineno = self.current_lineno
        raise ParseError(lineno, error_string)

    def parse_characters(self, count):
        assert len(self.lines[0]) >= count
        chars = self.lines[0][:count]
        self.lines[0] = self.lines[0][count:]
        self.current_colno += count
        return chars

    def skip_ws(self):
        while self.lines and self.lines[0] and self.lines[0][0] == ' ':
            self.parse_characters(1)

    def parse_token(self):
        self.skip_ws()
        start_col = self.current_colno
        token = parse_token(self.lines[0])
        if token == '':
            self.raise_error('unexpected end of line')
        self.parse_characters(len(token))
        return ParsedToken(token, FilePosition(self.path, self.current_lineno, start_col, self.current_colno))

    def parse_identifier(self):
        self.skip_ws()
        m = re.match(r'([a-zA-Z0-9_]*).*', self.lines[0])
        if m:
            identifier = m.group(1)
            self.parse_characters(len(identifier))
            return identifier
        else:
            self.raise_error('syntax error, expected identifier')

    def parse_string(self, string):
        self.skip_ws()
        if self.lines[0].startswith(string):
            self.parse_characters(len(string))
            return FilePosition(self.path, self.current_lineno, self.current_colno - len(string), self.current_colno)
        else:
            self.raise_error('syntax error, expected ' + string)

    def peek_string(self, string):
        self.skip_ws()
        return self.lines[0].startswith(string)

    def line_is_empty(self, in_cpp_code=False):
        line = self.lines[0].strip()
        return not line or (not in_cpp_code and line.startswith('#'))

    def parse_nl(self):
        if not self.line_is_empty():
            self.raise_error('unexpected token: ' + self.lines[0])
        self.skip_rest_of_line()

    def skip_rest_of_line(self, in_cpp_code=False):
        del self.lines[0]
        self.current_lineno += 1
        self.current_colno = 1
        while self.lines and self.line_is_empty(in_cpp_code):
            del self.lines[0]
            self.current_lineno += 1
        if self.lines:
            self.parse_current_indent()
        else:
            self.current_lineno = None
            self.current_indent = 0

    def parse_current_indent(self):
        i = 0
        while self.lines[0][i] == ' ':
            i += 1
        if self.lines[0][i] == '\t':
            self.raise_error('tab not allowed for indentation')
        if i % 4 != 0 and not self.parsing_action:
            self.raise_error('unaligned indentation')
        self.current_indent = i / 4
        self.parse_characters(i)

    def put_back(self, string):
        self.lines[0] = string + self.lines[0]
        self.current_colno -= len(string)

    def expect_indent(self, indent_level):
        if self.current_indent != indent_level:
            self.raise_error('unexpected indentation level')

    def strip_comment(self):
        if '#' in self.lines[0]:
            index = self.lines[0].find('#')
            self.lines[0] = self.lines[0][:index]

    def use_declaration(self, decl, kind):
        if decl.value:
            self.raise_error('multiple {} statements not allowed (previous declaration on line {})'.format(
                    kind, decl.lineno))
        decl.lineno = self.current_lineno

    def parse_include(self):
        words = self.lines[0].split(' ')
        if words[0].startswith('"') and words[0].endswith('"') or words[0].startswith('<') and words[0].endswith('>'):
            include = words[0]
            self.parse_characters(len(include))
            return include
        else:
            self.raise_error('incorrect include path syntax')

    def parse_includes(self, include_type_token):
        include_decl = {'HIncludes': self.h_includes,
                        'CppIncludes': self.cpp_includes,
                        'EscIncludes': self.esc_includes}[include_type_token]
        self.use_declaration(include_decl, include_type_token)
        self.parse_nl()
        while self.current_indent == 1:
            include = self.parse_include()
            include_decl.value.append(include)
            self.parse_nl()

    def parse_event_or_triggered_operation(self):
        name = self.parse_identifier()
        file_pos = FilePosition(self.path, self.current_lineno, self.current_colno - len(name), self.current_colno)
        params = []

        if not self.peek_string('('):
            self.parse_nl()
            return Event(name, file_pos)

        self.parse_string('(')
        if self.line_is_empty():
            self.parse_nl()
            while self.current_indent == 2:
                self.strip_comment()
                param_str = self.lines[0].strip(', ')
                param = parse_parameter(param_str, self.current_lineno)
                params.append(param)
                self.skip_rest_of_line()
            self.expect_indent(1)
            self.parse_string(')')
            self.parse_nl()
        else:
            self.strip_comment()
            param_strs = self.lines[0].strip(') ').split(',')
            for param_str in param_strs:
                param = parse_parameter(param_str, self.current_lineno)
                params.append(param)
            self.skip_rest_of_line()
        return Event(name, file_pos, params)

    def parse_events_or_triggered_operations(self, what):
        decl = {'Events': self.events,
                'TriggeredOperations': self.triggered_operations}[what]
        self.use_declaration(decl, what)
        self.parse_nl()
        while self.lines and self.current_indent == 1:
            ev_or_tg = self.parse_event_or_triggered_operation()
            decl.value.append(ev_or_tg)

    def parse_single_line_declaration(self, decl, what):
        self.use_declaration(decl, what)
        if self.peek_string('"'):
            rest = self.lines[0].strip()
            if rest[-1] != '"':
                self.raise_error('syntax error, missing " character')
            decl.value = rest[1:-1]
            self.skip_rest_of_line()
        else:
            token = self.parse_token()
            decl.value = token.string
            self.parse_nl()

    def parse_guard(self):
        self.parse_string('[')
        end = self.lines[0].find(']')
        if end == -1:
            self.raise_error('syntax error, missing ] character')
        guard = self.parse_characters(end).strip()
        self.parse_string(']')
        return CodeFragment(guard)

    def parse_action(self, inline=False):
        self.parsing_action = True
        file_pos = self.parse_string('/')
        if not self.line_is_empty():
            action = self.lines[0].strip()
            if not is_single_cpp_statement(action):
                # This is required in order to keep compatibility with Eclipse xtext plugin
                self.raise_error('same-line action must be a single C++ statement')
            self.skip_rest_of_line()
        else:
            action = ''
            orig_indent = self.current_indent
            self.parse_nl()
            min_indent = 2 if inline else 1
            while self.lines and self.current_indent >= orig_indent + min_indent:
                action += self.lines[0] + '\n'
                self.skip_rest_of_line(in_cpp_code=True)
        if not action:
            self.raise_error('action must not be empty', lineno=file_pos.line)
        self.parsing_action = False
        return CodeFragment(action, file_pos)

    def parse_transition(self, token):
        guard = None
        event_name = None
        internal = False
        if token.string == 'internal':
            internal = True
            token = self.parse_token()

        if token.string == '[':
            self.put_back('[')
            guard = self.parse_guard()
            file_pos = self.parse_string('->')
        elif token.string == '->':
            file_pos = token.file_pos
        else:
            event_name = token.string
            if self.peek_string('['):
                guard = self.parse_guard()
            if not internal:
                file_pos = self.parse_string('->')
            else:
                file_pos = token.file_pos

        if not internal:
            dest_state = self.parse_token()
        else:
            dest_state = ParsedToken('<internal>')

        if dest_state.string in ['state', 'choice', 'terminate']: # inline state
            orig_indent = self.current_indent
            action = None
            inline_type = dest_state.string
            if self.peek_string('/'):
                action = self.parse_action(inline=True)
            else:
                self.parse_nl()
            if inline_type == 'state':
                inline_s = State('', dest_state.file_pos, 'state', [])
            elif inline_type == 'choice':
                inline_s = State('Choice', dest_state.file_pos, 'choice', [])
            elif inline_type == 'terminate':
                inline_s = State('Terminate', dest_state.file_pos, 'terminate', [])

            while self.lines and self.current_indent > orig_indent:
                s_token = self.parse_token()
                s_stmt = self.parse_statement(s_token)
                inline_s.statements.append(s_stmt)

            use_history = None
            dest_state = inline_s
            inline_dest_state = True

        else:
            use_history = False
            if dest_state.string == 'history':
                use_history = True
                dest_state = self.parse_token()

            if self.peek_string('/'):
                action = self.parse_action()
            else:
                action = None
                self.parse_nl()

            inline_dest_state = False

        return Transition(event_name, dest_state, action, guard=guard, use_history=use_history,
                          inline_dest_state=inline_dest_state, file_pos=file_pos)

    def parse_statement(self, token):
        if token.string == 'entry':
            action = self.parse_action()
            return Entry(action)
        elif token.string == 'exit':
            action = self.parse_action()
            return Exit(action)
        else:
            return self.parse_transition(token)

    def parse_statements(self):
        state_stack = [(State('root', None, 'state', []), 0)]
        stmt_before_region_list = []
        while self.lines and self.current_indent > 0:

            if self.current_indent > state_stack[-1][1] + 1:
                self.raise_error('unexpected indentation level')
            while self.current_indent <= state_stack[-1][1]:
                del state_stack[-1]

            token = self.parse_token()

            if token.string.startswith('---'):
                stmt_before_region_list.append(state_stack[-1][0].statements[-1])
                self.skip_rest_of_line()
                continue

            state_types = {'choice': 'choice',
                           'junction': 'junction',
                           'join': 'join',
                           'subentry': 'entry connector',
                           'subexit': 'exit connector',
                           'connector': 'diagram connector',
                           'terminate': 'terminate'}

            state_type = state_types.get(token.string, 'state')
            if state_type is not 'state':
                token = self.parse_token()

            if self.line_is_empty():
                new_state = State(token.string, token.file_pos, state_type, [])
                state_stack[-1][0].statements.append(new_state)
                state_stack.append((new_state, self.current_indent))
                self.parse_nl()
            else:
                stmt = self.parse_statement(token)
                state_stack[-1][0].statements.append(stmt)

        root_state = state_stack[0][0]
        create_regions(root_state, stmt_before_region_list)
        return root_state.statements

    def parse_state_machine(self, sm_token):
        name = self.parse_token()
        self.parse_nl()
        is_sub_sm = (sm_token == 'SubStateMachine')
        statements = self.parse_statements()
        return name, is_sub_sm, statements

    def parse(self):
        if self.line_is_empty():
            self.skip_rest_of_line()
        while self.lines:
            token = self.parse_token().string
            if token in ['HIncludes', 'CppIncludes', 'EscIncludes']:
                self.parse_includes(token)
            elif token in ['Events', 'TriggeredOperations']:
                self.parse_events_or_triggered_operations(token)
            elif token == 'Namespace':
                self.parse_single_line_declaration(self.namespace, token)
            elif token in ['StateMachine', 'SubStateMachine']:
                name, is_sub_sm, statements = self.parse_state_machine(token)
                self.state_machines.append((name, is_sub_sm, statements))
            else:
                self.raise_error('unexpected token: ' + token)

        self.events.value = [Event(e.name, e.file_pos, e.params, self.namespace.value) for e in self.events.value]
        self.triggered_operations.value = [Event(e.name, e.file_pos, e.params, self.namespace.value) for e in self.triggered_operations.value]

        return self.h_includes.value, self.cpp_includes.value, self.esc_includes.value, \
            self.events.value, self.triggered_operations.value, self.namespace.value, self.state_machines


def parse_esc(path, esc_str):
    p = Parser(path, esc_str)
    return p.parse()


def find_include(base_path, include):
    path = include.strip('<>"')
    same = os.path.join(base_path, path)
    if os.path.exists(same):
        return same
    else:
        return path


def parse_esc_includes(base_path, esc_path, esc_includes):
    external_events = []
    for esc_include in esc_includes:
        include = find_include(base_path, esc_include)
        try:
            with file(include) as f:
                h_includes, cpp_includes, new_esc_includes, events, triggered_ops, namespace, state_machines = parse_esc(include, f.read())
                assert not new_esc_includes and not triggered_ops and not state_machines
                external_events += events
        except IOError as e:
            print str(e)
            sys.exit(1)
    return external_events


def parse_file(base_path, esc_path):
    with file(esc_path) as f:
        try:
            (h_includes, cpp_includes, esc_includes, events, triggered_ops,
             namespace, state_machines) = parse_esc(esc_path, f.read())
            external_events = parse_esc_includes(base_path, esc_path,
                                                 esc_includes)
            root_name = os.path.splitext(os.path.basename(esc_path))[0]
            return parse_tree.make_sm_file(h_includes, cpp_includes, esc_includes, events, external_events, triggered_ops, namespace, root_name, state_machines)
        except ParseError as p:
            print p.format(esc_path)
            sys.exit(1)

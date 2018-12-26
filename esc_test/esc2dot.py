import dot
import parser
import state_machine

import os
import sys
import textwrap

from collections import namedtuple

from args import EscArgumentParser


transition_states = set() # for unique naming


def make_transition_state_name(src, dest):
    name = src.name + '_To_' + dest.name
    candidate = name
    i = 2
    while candidate in transition_states:
        candidate = name + str(i)
        i += 1
    transition_states.add(candidate)
    return candidate


def escape(string):
    return string.replace('\\', '\\\\').replace('"', '\\"').replace('\n', '\\l')


def strip(string):
    if string:
        return string.strip()


def fully_qualified_name(state):
    names = []
    while state.parent:
        if not state.is_region:
            names.append(state.name)
        state = state.parent
    names.append(state.sm.full_cpp_class_name)
    return '.'.join(reversed(names))


def make_start_state(containing_state):
    name = 'StartState'
    if containing_state.parent:
        if containing_state.parent.is_region_root:
            index = containing_state.parent.children.index(containing_state) + 1
            name += containing_state.parent.name + 'Ort' + str(index)
        else:
            name += containing_state.name
    state = dot.State(name)
    state.properties = {'label': '""', 'width': '0.1', 'height': '0.1', 'style': 'filled', 'fillcolor': 'black'}
    return state


def linebreak(string):
    result = []
    for part in string.split('\n'):
        new_part = textwrap.fill(part, subsequent_indent='    ', break_long_words=False, break_on_hyphens=False)
        result.append(new_part)
    string = '\n'.join(result)
    if '\n' in string and not string.endswith('\n'):
        string += '\n'
    return string


def make_transition_state(src, dest, url, action):
    state = dot.State(make_transition_state_name(src, dest))
    state.properties = {'shape': 'rect', 'margin': '0,0', 'width': '0', 'height': '0',
                        'color': 'white', 'fontsize': '10', 'label': '"' + escape(linebreak(action)) + '"',
                        'fontname': 'Arial'}
    if url:
        state.properties['URL'] = url
    return state


def get_event_name(event):
    if event.name.startswith('evTimer'):
        return 'tm(' + str(event.timeout) + ')'
    else:
        return event.name


def make_internal_box(state):

    def make_trans_str(trans):
        trans_str = get_event_name(trans.event)
        if trans.guard:
            trans_str += '[' + trans.guard.code + ']'
        if trans.action:
            action = strip(trans.action.code).replace('\n', '\n   ')
            if trans_str:
                trans_str += ' /\n   ' + action
            else:
                trans_str = ' / ' + action
        prefix = ''
        if trans.use_history:
            prefix += '[HIST] '
        return prefix + trans_str

    lines = []
    if state.entry_action:
        lines.extend(['[ENTER]', strip(state.entry_action.code)])
    if state.exit_action:
        lines.extend(['[EXIT]', strip(state.exit_action.code)])
    if get_self_transitions(state):
        lines.append('[SELF]')
        for trans in get_self_transitions(state):
            trans_str = make_trans_str(trans)
            lines.append(trans_str)
    if get_internal_transitions(state):
        lines.append('[INTERNAL]')
        for trans in get_internal_transitions(state):
            trans_str = make_trans_str(trans)
            lines.append(trans_str)

    contents = '\n'.join(lines) + '\n'
    return dot.State('InternalBox' + state.name, {'shape': 'box', 'fontsize': '10', 'label': '"' + escape(contents) + '"',
                                                  'fontname': 'Arial', 'style': 'filled', 'fillcolor': 'cornsilk'})


def make_shadow_box(state):
    return dot.State('ShadowState' + state.name, {'style': 'invisible'})


def find_inner_dot_state_name(state):
    if needs_internal_box(state):
        return 'InternalBox' + state.name
    else:
        return 'ShadowState' + state.name


def add_transition(context, digraph, src, dest, parent, url, action, use_history=False):
    def get_name_and_props(state, arrow_part):
        if needs_subgraph(state):
            state_name = find_inner_dot_state_name(state)
            props = [(arrow_part, 'cluster' + state.name), ('minlen', '2')]
            return state_name, props
        else:
            return state.name, []
    src_name, src_props = get_name_and_props(src, 'ltail')
    dest_name, dest_props = get_name_and_props(dest, 'lhead')

    if use_history:
        dest_name = 'History' + dest.name
        dest_props = []

    common_props = [('color', 'firebrick'), ('penwidth', '2')]
    if url:
        common_props += [('URL', url)]

    if not action:
        context.transitions.append(dot.Transition(src_name, dest_name, dict(src_props + dest_props + [('minlen', '2')] + common_props)))
    else:
        trans_state = make_transition_state(src, dest, url, action)
        context.transition_states.append((trans_state, parent))
        context.transitions.append(dot.Transition(src_name, trans_state.name, dict(src_props + [('dir', 'none')] + common_props)))
        context.transitions.append(dot.Transition(trans_state.name, dest_name, dict(dest_props + common_props)))


def get_self_transitions(state):
    return [t for t in state.transitions if t.dest_state is state]


def get_internal_transitions(state):
    return [t for t in state.transitions if t.dest_state is None]


def get_arrow_transitions(state):
    return [t for t in state.transitions
            if not (t.dest_state is state or
                    isinstance(t.event, state_machine.Default) or
                    t.dest_state is None)]


def needs_internal_box(state):
    return state.entry_action or state.exit_action or get_self_transitions(state) or get_internal_transitions(state)


def needs_subgraph(state):
    return hasattr(state, 'children') and (state.children or needs_internal_box(state))


def add_start_state(context, graph, containing_state, default_transition=None):
    start_state = make_start_state(containing_state)
    graph.add_state(start_state)

    def_trans = default_transition if default_transition else containing_state.default_transition

    url = None
    if def_trans.action:
        url = make_url(def_trans.file_pos)

    add_transition(context, graph, start_state, def_trans.dest_state, containing_state, url, strip('/ ' + def_trans.action.code if def_trans.action else None))


def make_history_state(containing_state):
    return dot.State('History' + containing_state.name, {'label': 'H'})


def needs_history_state(sm, state):
    return any([trans for st, trans in sm.all_transitions()
                if trans.dest_state is state and st is not state and trans.use_history])


def make_url(file_pos):
    return '"#{}:{}-{}"'.format(file_pos.line - 1, file_pos.start_col - 1, file_pos.end_col - 2)


def add_state(sm, context, graph, state):
    if needs_subgraph(state):
        qname = '"' + fully_qualified_name(state) + '"'
        sub = dot.Graph('subgraph', 'cluster' + state.name, {'label': state.name, 'style': 'rounded', 'fontname': 'Arial', 'fontcolor': 'darkgreen',
                                                             'id': qname, 'URL': make_url(state.file_pos)})

        if needs_internal_box(state):
            sub.add_state(make_internal_box(state))
        else:
            sub.add_state(make_shadow_box(state))

        # Display null transition into a child object (like a condition point) as a default transition to the child object
        if not state.default_transition:
            for trans in state.transitions:
                if trans.dest_state in state.children and not trans.event:
                    add_start_state(context, sub, state, trans)
                    state.transitions.remove(trans)
                    break

        if not state.is_region_root and state.children:
            for sub_state in state.children:
                add_state(sm, context, sub, sub_state)
            if state.default_transition:
                add_start_state(context, sub, state)

        elif state.is_region_root:
            for conn in [c for c in state.children if not c.is_region]:
                add_state(sm, context, sub, conn)
            for i, region in enumerate([c for c in state.children if c.is_region]):
                props = {'style': 'dotted', 'label': '""'}
                region_graph = dot.Graph('subgraph', 'cluster' + state.name + 'Ort' + str(i+1), props)
                for region_substate in region.children:
                    add_state(sm, context, region_graph, region_substate)
                add_start_state(context, region_graph, region)
                sub.add_subgraph(region_graph)
                context.state_graph_map[region] = region_graph

        if needs_history_state(sm, state):
            sub.add_state(make_history_state(state))

        graph.add_subgraph(sub)
        context.state_graph_map[state] = sub

    else:
        if state.is_choice:
            props = {'label': 'C', 'width': '0.3', 'height': '0.2', 'margin': '0,0', 'fontsize': '18', 'fillcolor': 'lightblue', 'style': 'filled'}
        elif state.is_junction:
            props = {'label': '""', 'width': '0.2', 'height': '0.2', 'fillcolor': 'lightblue', 'style': 'filled'}
        elif state.is_terminate:
            props = {'label': '""', 'shape': 'doublecircle', 'width': '0.3', 'height': '0.3'}
        elif state.is_diagram_connector:
            props = {'shape': 'rect', 'style': 'filled', 'fontname': 'Arial', 'fontcolor': 'black', 'fillcolor': 'lightblue'}
            if '__' in state.name:
                props['label'] = state.name[:-3]
        elif state.is_entry_connector or state.is_exit_connector:
            props = {'shape': 'rect', 'style': 'filled', 'fontname': 'Arial', 'fontcolor': 'black', 'fillcolor': 'plum'}
        elif state.is_join:
            props = {'shape': 'rect', 'label': '""', 'width': '1', 'height': '0.2', 'margin': '0,0', 'fillcolor': 'lightblue', 'style': 'filled'}
        else:
            props = {'shape': 'rect', 'style': 'rounded', 'fontname': 'Arial', 'fontcolor': 'darkgreen'}
            if 'Inline' in state.name:
                props['label'] = 'Tmp'
                props['fontcolor'] = 'black'
                props['fontsize'] = '12'
        qname = '"' + fully_qualified_name(state) + '"'
        props['id'] = qname
        props['URL'] = make_url(state.file_pos)
        graph.add_state(dot.State(state.name, props))

    for trans in get_arrow_transitions(state):
        label = get_event_name(trans.event) if trans.event else ''
        if trans.guard:
            label += '[' + trans.guard.code + ']'
        if state.is_choice and not trans.guard:
            label += '[else]'
        qname = '"' + fully_qualified_name(state) + '#' + label + '"'
        if trans.action:
            action = strip(trans.action.code)
            if label:
                label += ' /\n' + action
            else:
                label += ' / ' + action
        url = make_url(trans.file_pos)
        parent = state_machine.calc_common_state(state, trans.dest_state)
        if parent is state or parent is trans.dest_state:
            parent = parent.parent
        add_transition(context, graph, state, trans.dest_state, parent, url, label, trans.use_history)


def place_transition_states(context, root_graph):
    "Transition states should be in the parent state of either the source state or the dest state, whichever is closest to the root"
    for trans_state, parent_state in context.transition_states:
        if parent_state is None:
            graph = root_graph
        else:
            graph = context.state_graph_map[parent_state]
        graph.add_state(trans_state)


Context = namedtuple('Context', ['transitions', 'transition_states', 'state_graph_map'])


def make_dot(sm, root_state):
    dg = dot.Graph('digraph', 'Sm')
    dg.properties['compound'] = 'true'
    dg.properties['smoothing'] = 'true'
    dg.properties['splines'] = 'polyline'

    context = Context([], [], {root_state: dg})

    if sm.is_sub_sm:
        add_state(sm, context, dg, root_state)
    else:
        if root_state.default_transition:
            add_start_state(context, dg, root_state)
        for state in root_state.children:
            add_state(sm, context, dg, state)

    place_transition_states(context, dg)

    dg.transitions = context.transitions

    return dg.output()


def add_multiple_local_diagram_connectors(root_state):
    new_connector_map = {}
    for state in state_machine.walk_states(root_state, include_all=True):
        for trans in state.transitions:
            if trans.dest_state and trans.dest_state.is_diagram_connector:
                new_connector = new_connector_map.get((trans.dest_state, trans.connector_number), None)
                if not new_connector:
                    connector_number = trans.connector_number if trans.connector_number is not None else 0
                    new_name = trans.dest_state.name + '__' + str(connector_number)
                    new_connector = state_machine.State(new_name, trans.dest_state.file_pos, [], None, None, 'diagram connector')
                    state.parent.add_child(new_connector)
                    new_connector_map[(trans.dest_state, connector_number)] = new_connector
                trans.dest_state = new_connector


def add_extra_diagram_connectors(root_state):
    add_multiple_local_diagram_connectors(root_state)


def generate(base_path, esc_path, out_path):
    result = []
    sm_file = parser.parse_file(base_path, esc_path)

    for sm in sm_file.state_machines:
        state_machine.resolve_inline_states(sm)
        add_extra_diagram_connectors(sm.root_state)
        full_name = sm_file.name + '.' + sm.prefix_name
        dot_path = os.path.join(out_path, full_name) + '.dot'
        with file(dot_path, 'w') as f:
            f.write(make_dot(sm, sm.root_state))
        result.append(dot_path)

    return result


def generate_esc(base_path, esc_path, output_dir):
    if not output_dir:
        output_dir = base_path

    return generate(base_path, esc_path, output_dir)


def parse_args():
    description = ('Generate .dot file from ESC Statechart description (.esc) '
                   'file.')
    arg_parser = EscArgumentParser(description=description)
    return arg_parser.parse_args()


def main():
    args = parse_args()
    for path in generate_esc(args.base_path, args.esc_file, args.output_dir):
        print path


if __name__ == '__main__':
    try:
        main()
    except IOError, e:
        print(e.message)
        sys.exit(1)

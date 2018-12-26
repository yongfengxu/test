
def indent(ind, string):
    return '    ' * ind + string


def make_properties_str(props):
    if not props:
        return ''
    else:
        return ' [' + ', '.join([key + '=' + val for key, val in props.items()]) +']'


class Graph(object):
    def __init__(self, graph_type, name, properties=None):
        self.graph_type = graph_type
        self.name = name
        self.properties = properties if properties else {}
        self.subgraphs = []
        self.states = []
        self.transitions = []
        self.parent = None

    def add_state(self, state):
        state.parent = self
        self.states.append(state)

    def add_subgraph(self, subgraph):
        subgraph.parent = self
        self.subgraphs.append(subgraph)

    def output(self, ind=0):
        ret = indent(ind, '%s %s {\n' % (self.graph_type, self.name))

        for key, val in self.properties.items():
            ret += indent(ind + 1, '%s=%s;\n' % (key, val))

        for subgraph in self.subgraphs:
            ret += subgraph.output(ind + 1)

        for state in self.states:
            ret += state.output(ind + 1)

        for transition in self.transitions:
            ret += transition.output(ind + 1)

        ret += indent(ind, '}\n')
        return ret


class State(object):
    def __init__(self, name, properties=None):
        self.name = name
        self.properties = properties if properties else {}
        self.parent = None

    def output(self, ind):
        return indent(ind, '%s%s;\n' % (self.name, make_properties_str(self.properties)))


class Transition(object):
    def __init__(self, src, dest, properties=None):
        self.src = src
        self.dest = dest
        self.properties = properties if properties else {}

    def output(self, ind):
        return indent(ind, '%s -> %s%s;\n' % (self.src, self.dest, make_properties_str(self.properties)))

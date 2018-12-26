import esc2dot
import os
import sys

from args import EscArgumentParser


def parse_args():
    description = ('Generate SVG representation from ESC Statechart '
                   'description (.esc) file. One SVG file will be produced '
                   'per state machine except when piping from stdin, in which '
                   'case a single SVG containing all state machines is '
                   'generated on stdout.')
    arg_parser = EscArgumentParser(description=description)
    return arg_parser.parse_args()


def main():
    args = parse_args()
    dot_paths = esc2dot.generate_esc(args.base_path, args.esc_file,
                                     args.output_dir)
    if args.esc_file == '/dev/stdin':
        cmd_pipe = ['dot ' + ' '.join(dot_paths),
                    'gvpack 2>/dev/null',
                    'neato -s -n2 -Tsvg']
        os.system('|'.join(cmd_pipe))
    else:
        for dot_path in dot_paths:
            svg_path = dot_path.replace('.dot', '.svg')
            print svg_path
            os.system('dot -Tsvg ' + dot_path + ' > ' + svg_path)


if __name__ == '__main__':
    try:
        main()
    except IOError, e:
        print(e.message)
        sys.exit(1)

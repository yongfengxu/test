import argparse
import os


def arg_check_esc_file(value):
    if value != '-' and not value.endswith('.esc'):
        raise argparse.ArgumentTypeError('Input file must have .esc '
                                         'extension!')
    return value


class EscArgumentParser(argparse.ArgumentParser, object):
    def __init__(self, *args, **kwargs):
        super(EscArgumentParser, self).__init__(args, kwargs)
        self.add_argument('esc_file', type=arg_check_esc_file,
                          help='Path to ESC file or - to read from stdin.')
        self.add_argument('-b', '--base-path',
                          help=('Include path for referenced ESC files.  If '
                                'not set it will default to the directory of '
                                'the specified ESC file.'))
        self.add_argument('-o', '--output-dir',
                          help=('Output directory for generated files '
                                '(default: the directory containing the input '
                                '.esc file).'))

    def parse_args(self):
        args = super(EscArgumentParser, self).parse_args()
        if args.esc_file == '-':
            args.esc_file = '/dev/stdin'
            if not args.output_dir:
                args.output_dir = os.getcwd()
        elif not args.base_path:
            args.base_path = os.path.dirname(args.esc_file)

        return args

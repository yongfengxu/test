#!/lab/epg_st_utils/lao/rhes6.x86_64/bin/python

import argparse

SUMMARY_HTML = "hello"
parser = argparse.ArgumentParser()

parser.add_argument('--report_php_filename', help='...',required=False)
args = parser.parse_args()
if args.report_php_filename:
        SUMMARY_HTML = args.report_php_filename


print SUMMARY_HTML

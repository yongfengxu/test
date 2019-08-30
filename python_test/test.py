#!/home/elmpprv/projs/bin/python3
import os
import argparse
import subprocess
import yaml
import xlwt
from datetime import datetime

style0 = xlwt.easyxf('font: name Times New Roman, color-index red, bold on',
    num_format_str='#,##0.00')
style1 = xlwt.easyxf(num_format_str='D-MMM-YY')

wb = xlwt.Workbook()
ws = wb.add_sheet('A Test Sheet')

ws.write(0, 0, 1234.56, style0)
ws.write(1, 0, datetime.now(), style1)
ws.write(2, 0, 1)
ws.write(2, 1, 1)
ws.write(2, 2, xlwt.Formula("A3+B3"))

wb.save('example.xls')

TAGS = "NOT_CONFIG_EPG_3,CUPS_T2_INT,NOT_READY_EPG_3,CUPS_T2"

real_tags = ["NOT_CONFIG_EPG_3", "A", "B"]
real_tags1 = ["CCC", "A", "B"]

if not any (key in real_tags for key in TAGS.split(',')):
	print("we find you")
else:
	print(real_tags)



testcases = {"1": "2"}
wip = ['1']
not_ready = ['1']
cups_t2 = ['1']
not_tagged = ['1']

print("all: %d, WIP: %d, NOT READY: %d, CUP_T2: %d, NOT TAGGED: %d\n" % (len(testcases), len(wip), len(not_ready), len(cups_t2), len(not_tagged))) 


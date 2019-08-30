#!/home/elmpprv/projs/bin/python3
import os
import argparse
import subprocess
import yaml
import xlwt

TAGS = "WIP,NOT_CONFIG_EPG_3,CUPS_T2_INT,NOT_READY_EPG_3,CUPS_T2_BASIC,CUPS_T2"
WIP = "WIP"
NOTCONFIG = "NOT_CONFIG_EPG_3"
NOTREADY = "NOT_READY_EPG_3"
CUPST2 = "CUPS_T2_INT,CUPS_T2_BASIC,CUPS_T2"

def parse_yaml(filenames):

	testcases = {}

	for filename in filenames:
		#print("trying to read file: " + filename)

		with open(filename, 'r') as f:
			for tc in yaml.full_load(f)['testcases']:
				testcases[tc['name']] = tc['tags']
				#if not any(key in tc['tags'] for key in TAGS.split(',')):
				#	testcases.append(tc['name'])

	return testcases

def find_no_tagged_tc(filenames):
	testcases = []

	for filename in filenames:
		#print("trying to read file: " + filename)

		with open(filename, 'r') as f:
			for tc in yaml.load(f)['testcases']:
				if not any(key in tc['tags'] for key in TAGS.split(',')):
					testcases.append(tc['name'])
	return testcases


def analyse_testcases(testcases):
	"""{'TCName':'[tag1, tag2,..]'} """
	wip = []
	not_ready = []
	cups_t2 = []
	not_config = []
	no_tags = []

	for (tc, tags) in testcases.items():
		for tag in tags:
			if not any(key in tags for key in TAGS.split(',')):
				no_tags.append(tc)
			elif (tag == WIP):
				wip.append(tc)
				break
			elif (tag == NOTREADY):
				not_ready.append(tc)
				break
			elif (tag == NOTCONFIG):
				not_config.append(tc)
			elif (tag.startswith("CUPS_T2")):
				cups_t2.append(tc)
				break

	print("all: %d, WIP: %d, NOT_READY_EPG_3: %d, CUP_T2: %d, NOT_CONFIG_EPG_3: %d, NO_TAGS: %d\n" % (len(testcases), len(wip), len(not_ready), len(cups_t2), len(not_config), len(no_tags)))

	workbook = create_execl()

	save_to_sheet(workbook, WIP, wip)
	save_to_sheet(workbook, NOTREADY, not_ready)
	save_to_sheet(workbook, "CUPS_T2",cups_t2)
	save_to_sheet(workbook, NOTCONFIG, not_config)
	save_to_sheet(workbook, "NO_TAGS", no_tags)

	save_execl(workbook)


def create_execl():
	wb = xlwt.Workbook()
	return wb

def save_execl(wb):
	wb.save('SGW_FT_PORTING_STATISTICS.xls')

def save_to_sheet(wb, name, list):
	ws = wb.add_sheet(name)

	raw = 0
	for v in list:
		ws.write(raw, 0, v)
		raw += 1



def find_files(input_suites_filename):

	suites = []
	filenames_whole_path = []

	with open(input_suites_filename, 'r') as f:
		for line in f.readlines():
			suites.append(line.rstrip('\n'))

	env_dist = os.environ
	suites_path = env_dist["TTCN3_GGSN_ROOT_PATH"] + "/testsuites/"


	for suite in suites:
		command = "find " + suites_path + " -name " + suite	 + " -type f "
		p = subprocess.Popen(command, stdout=subprocess.PIPE, shell=True)
		p.wait()
		result = p.stdout.read().splitlines()
		for v in result:
			filenames_whole_path.append(v.decode('utf-8'))

	#print (filenames_whole_path)
	return filenames_whole_path

def main():
	argparser = argparse.ArgumentParser(description='find and copy cmakefile')
	#argparser.add_argument('--path', nargs='*', help='Input folder path')
	argparser.add_argument('--file',  help='Input suites file')
	args = argparser.parse_args()

	if args.file is None:
		print ("Please input the file name includes all suites to be analysed")
		return

	files = find_files(args.file)
	tcs = parse_yaml(files)
	analyse_testcases(tcs)


	#print(str(len(no_taged_tc)) + " TCs should be tagged\n")
	#print(no_taged_tc)

if __name__ == '__main__':
	main()

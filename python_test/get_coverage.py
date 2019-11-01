#!/home/elmpprv/projs/bin/python3
import os
import argparse
import subprocess
import urllib3
import json
import jsonpath

#get coverage monitor directorys

def getBuildCoverageResult(buildID):

	http = urllib3.PoolManager()
	r = http.request('GET', GET_COVERAGE_LINK.format(buildID))
	#print(r.status) # 200
	if r.status == 200:
		calculateCoverage(r.data.decode())
	else:
		print("failed to get {} raw coverage information".format(buildID))

def calculateCoverage(data):
	covered = 0
	lines = 0

	js = json.loads(data)
	#gtp = jsonpath.jsonpath(js,'$..success')

	for dir in SGW_DIRECTORY.split(','):
		summary = jsonpath.jsonpath(js,'$..{}.summary'.format(dir))
		covered += summary[0]['covered']
		lines += summary[0]['lines']
		#print(dir + " covered: " + str(summary[0]['covered']) + " lines: " + str(summary[0]['lines'])
	print(" covered: {0} lines: {1} average: {2:10.2f}%".format(covered, lines, covered*100/lines))

def main():
	argparser = argparse.ArgumentParser(description='input build id')
	argparser.add_argument('--buildID',  help='Input build id')
	args = argparser.parse_args()

	if args.buildID is None:
		print ("Please input the file name includes all suites to be analysed")
		return

	result = getBuildCoverageResult(args.buildID)


if __name__ == '__main__':
	main()


#!/usr/bin/python
import os
import argparse
import subprocess

REPO="/repo/elmpprv/epg/application/"

def find_cmake_file(path):

    command = "find " + path + " -name \"CMakeLists.txt\" "
   # command = "find " + path + " -name \"CMakeLists.txt\" | xargs -n1"
    print command
    p = subprocess.Popen(command, stdout=subprocess.PIPE, shell=True)
    p.wait()
    #files = p.stdout.readlines()
    files = p.stdout.read().splitlines()

    print files
    return files

def copy_cmake_file(files):
    for file in files:
        dest = REPO + file
	subprocess.call(["cp", file, dest])
        #print "source: ", file
        #print "dest: ", dest

def main():
    argparser = argparse.ArgumentParser(description='find and copy cmakefile')
    #argparser.add_argument('--path', nargs='*', help='Input folder path')
    argparser.add_argument('--path',  help='Input folder path')
    args = argparser.parse_args()

    if args.path is None:
        print "Please input path"
        return 

    files = find_cmake_file(args.path)

    copy_cmake_file(files)

if __name__ == '__main__':
    main()

#!/usr/bin/python

a = 0

def test1():
    global a
    print(a)


def test2():
    global a
    print("in test2():{}".format(a))


def main():
    global a
    a = 1
    print("in main():{}".format(a))
    test1()
    test2()

if __name__ == '__main__':
	main()



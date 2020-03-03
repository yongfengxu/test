#!/home/elmpprv/projs/bin/python3
import threading
import time

def sing():
    for i in range(5):
        print("sing\n")
        time.sleep(1)

def dance():
    for i in range(5):
        print("dance\n")
        time.sleep(1)

def main():
    t1 = threading.Thread(target=sing)
    t2 = threading.Thread(target=dance)

    t1.start()
    t2.start()

def say():
    print("I'm sorry!")

if __name__ == "__main__":
    main()


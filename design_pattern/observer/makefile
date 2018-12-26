all: main

#CXX=/app/gcc/4.8.1/LMWP3/bin/g++ -std=c++11 -g
CXX = g++

main:ConcreteSubject.o ConcreteObserver.o main.o
	$(CXX) ConcreteSubject.o ConcreteObserver.o main.o -o main

ConcreteSubject.o: ConcreteSubject.cpp

ConcreteObserver.o: ConcreteObserver.cpp

clean: 
	rm -rf *.o $(all)

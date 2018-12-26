all:test fetch boost_test iterator_test shared_ptr_test window_test bool_test map_test set_test

CXX=/app/gcc/4.8.1/LMWP3/bin/g++ -std=c++11 -g

test:test.o
	g++ test.o -g -o test

fetch:sync_fetch_add.o
	g++ sync_fetch_add.o -lpthread -march=i686 -o fetch

boost_test:boost_test.o
	g++ boost_test.o -o boost_test

iterator_test:iterator_test.o
	g++ iterator_test.o -o iterator_test

shared_ptr_test:shared_ptr_test.o
	g++ shared_ptr_test.o -o shared_ptr_test

window_test:window_test.o
	g++ window_test.o -o window_test

bool_test:bool_test.o
	g++ bool_test.o -o bool_test

map_test:map_test.o
	g++ map_test.o -o map_test

set_test:set_test.o
	$(CXX) set_test.o -o set_test

clean: 
	rm -rf *.o $(all)


CXX=/app/gcc/4.8.1/LMWP3/bin/g++ -std=c++11 -g
TEST_BASE_PATH=~/test/advanced_cpp
#TEST_BASE_PATH=./


SOURCES := $(shell find $(TEST_BASE_PATH) -name "*.cpp" | xargs -i basename {})
OBJECTS:= $(SOURCES:.cpp=.o)
TARGETS := $(SOURCES:.cpp=)

#$(info  $(SOURCES))
#$(info  $(OBJECTS))
#$(info  $(TARGETS))

all: $(TARGETS)

#$(CXX) $^ -o $@

clean:
	rm -rf *.o $(TARGETS)


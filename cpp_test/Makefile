
#TEST_BASE_PATH=~/test/advanced_cpp
TEST_BASE_PATH=./

CC      := gcc
CXX     := clang++
#CXX     := clang++
LIBS    :=
LDFLAGS :=
DEFINES :=
INCLUDE := -I.
CFLAGS  := -g -std=c++17 -fsanitize=address -fsanitize-address-use-after-scope -fno-omit-frame-pointer -Wall -O $(DEFINES) $(INCLUDE)

CXXFLAGS:= $(CFLAGS) -DHAVE_CONFIG_H

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


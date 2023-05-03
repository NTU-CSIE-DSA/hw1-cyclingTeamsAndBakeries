SOURCES := $(wildcard *.cpp)
EXECUTABLES := $(SOURCES:%.cpp=%.exe)

.PHONY: all clean

all: $(EXECUTABLES)

clean:
	rm -f *.exe

%.exe: %.cpp testlib.h
	g++ -std=c++14 -Wall -Wextra -O2 $< -o $@

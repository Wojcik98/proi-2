CXX=g++
CXXFLAGS=-g -std=c++11 -Wall
BIN=calc
TESTDIR=test

SRC=$(wildcard *.cpp)
OBJ=$(SRC:%.cpp=%.o)

TESTSRC=tests/test.cpp tests/testConverter.cpp tests/testMath.cpp tests/testVariable.cpp
TESTOBJ=tests/test.o tests/testConverter.o tests/testMath.o tests/testVariable.o

all: $(OBJ)
	$(CXX) -o $(BIN) $^

%.o: %.c
	$(CXX) $@ -c $<

clean:
	rm -f *.o
	rm $(BIN)

test: $(TESTOBJ) Converter.o Variable.o Math.o
	$(CXX) -o test.out $^
	@./test.out

run: all
	@./$(BIN)

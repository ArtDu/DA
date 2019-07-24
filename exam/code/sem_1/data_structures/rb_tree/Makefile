CC = g++
FLAGS = -std=c++11 -g
SOURCES = lab2.cpp TTree.cpp
EXECUTABLE = lab2
all: build

build: lab2.cpp TTree.cpp
	$(CC) $(FLAGS) -o $(EXECUTABLE) $(SOURCES)

lab2.o: lab2.cpp TTree.h
	$(CC) $(FLAGS) -c lab2.cpp

TTree.o: TTree.cpp TTree.h
	$(CC) $(FLAGS) -c TTree.cpp


clean:
	rm -f *.o

CC = g++
FLAGS = -std=c++11 -g
SOURCES = main.cpp TTree.cpp
EXECUTABLE = main
all: build

build: main.cpp TTree.cpp
	$(CC) $(FLAGS) -o $(EXECUTABLE) $(SOURCES)

main.o: main.cpp TTree.h
	$(CC) $(FLAGS) -c main.cpp

TTree.o: TTree.cpp TTree.h
	$(CC) $(FLAGS) -c TTree.cpp


clean:
	rm -f *.o

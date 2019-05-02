CC = g++
FLAGS = -std=c++11 -g -pedantic -Wall -Werror -Wno-sign-compare -Wno-long-long -lm
SOURCES = main.cpp TSuffixTree.cpp
EXECUTABLE = main
all: build

build: main.cpp TSuffixTree.cpp
	$(CC) $(FLAGS) -o $(EXECUTABLE) $(SOURCES)

main.o: main.cpp TSuffixTree.h
	$(CC) $(FLAGS) -c main.cpp

TSuffixTree.o: TSuffixTree.cpp TSuffixTree.h
	$(CC) $(FLAGS) -c TSuffixTree.cpp

clean:
	rm -f *.o

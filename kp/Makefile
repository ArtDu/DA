CC = g++
FLAGS = -std=c++11 -g -pedantic -Wall -Werror -Wno-sign-compare -Wno-long-long -lm
SOURCES = main.cpp simple9.cpp invertedIndex.cpp
EXECUTABLE = main
all: build

build: main.cpp simple9.cpp invertedIndex.cpp
	$(CC) $(FLAGS) -o $(EXECUTABLE) $(SOURCES)

main.o: main.cpp invertedIndex.h simple9.h
	$(CC) $(FLAGS) -c main.cpp

invertedIndex.o: invertedIndex.cpp invertedIndex.h
	$(CC) $(FLAGS) -c invertedIndex.cpp

simple9.o: simple9.cpp simple9.h
	$(CC) $(FLAGS) -c simple9.cpp

clean:
	rm -f *.o

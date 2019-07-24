CC = g++
FLAGS = -std=c++11 -g -std=c++11 -pedantic -Wall -Werror -Wno-sign-compare -Wno-long-long -lm
SOURCES = main.cpp KeysTree.cpp
EXECUTABLE = main
all: build

build: main.cpp KeysTree.cpp
	$(CC) $(FLAGS) -o $(EXECUTABLE) $(SOURCES)

main.o: main.cpp KeysTree.h
	$(CC) $(FLAGS) -c main.cpp

KeysTree.o: KeysTree.cpp KeysTree.h
	$(CC) $(FLAGS) -c KeysTree.cpp

clean:
	rm -f *.o

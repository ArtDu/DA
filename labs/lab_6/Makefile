CC = g++
FLAGS = -std=c++11 -g -pedantic -Wall -Werror -Wno-sign-compare -Wno-long-long -lm
SOURCES = main.cpp TLongInt.cpp
EXECUTABLE = main
all: build

build: main.cpp TLongInt.cpp
	$(CC) $(FLAGS) -o $(EXECUTABLE) $(SOURCES)

main.o: main.cpp TLongInt.h
	$(CC) $(FLAGS) -c main.cpp

TLongInt.o: TLongInt.cpp TLongInt.h
	$(CC) $(FLAGS) -c TLongInt.cpp

clean:
	rm -f *.o

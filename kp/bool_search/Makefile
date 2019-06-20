CC = g++
FLAGS = -std=c++11 -O2 -g -pedantic -Wall -Werror -Wno-sign-compare -Wno-long-long -lm
SOURCES = main.cpp TSimple9.cpp TInvertedIndex.cpp TEnc.cpp
EXECUTABLE = main
all: build

build: main.cpp TSimple9.cpp TInvertedIndex.cpp
	$(CC) $(FLAGS) -o $(EXECUTABLE) $(SOURCES)

main.o: main.cpp TInvertedIndex.h TSimple9.h
	$(CC) $(FLAGS) -c main.cpp

TInvertedIndex.o: TInvertedIndex.cpp TInvertedIndex.h
	$(CC) $(FLAGS) -c TInvertedIndex.cpp

TSimple9.o: TSimple9.cpp TSimple9.h
	$(CC) $(FLAGS) -c TSimple9.cpp

TEnc.o: TEnc.cpp TEnc.h
	$(CC) $(FLAGS) -c TEnc.cpp

clean:
	rm -f *.o

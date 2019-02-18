CC = g++
FLAGS = -std=c++11 -g -pedantic -Wall -Werror -Wno-sign-compare -Wno-long-long -lm
SOURCES = lab1.o TVector.o
EXECUTABLE = lab1
all: build

build: lab1.o TVector.o
	$(CC) $(FLAGS) -o $(EXECUTABLE) $(SOURCES)

lab1.o: lab1.cpp TVector.h
	$(CC) $(FLAGS) -c lab1.cpp


TVector.o: TVector.cpp TVector.h
	$(CC) $(FLAGS) -c TVector.cpp


clean:
	rm -f $(SOURCES)

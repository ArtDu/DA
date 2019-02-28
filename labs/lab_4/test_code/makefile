CC = g++
FLAGS = -std=c++11 -g -pedantic -Wall -Werror -Wno-sign-compare -Wno-long-long -lm
SOURCES = main.cpp
EXECUTABLE = lab4
all: build

build: main.cpp
	$(CC) $(FLAGS) -o $(EXECUTABLE) $(SOURCES)

main.o: main.cpp
	$(CC) $(FLAGS) -c main.cpp

clean:
	rm -f *.o

CC = g++
FLAGS = -std=c++11 -Wextra -Wall -Werror -Wno-sign-compare -Wno-unused-result -pedantic -O2 
FILES = TBohr.cpp main.cpp
PROG = aho
all: aho
	
aho:
	$(CC) $(FLAGS) -o $(PROG) $(FILES)

clean:
	rm -f *.o aho
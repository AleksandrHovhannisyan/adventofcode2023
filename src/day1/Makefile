CC = g++
CFLAGS = -std=c++20 -Wall

.PHONY: all clean

all: utils.o 01 02

utils.o: ../utils.h ../utils.cpp
	$(CC) $(CFLAGS) -c ../utils.cpp

01: 01.cpp utils.o
	$(CC) $(CFLAGS) -o 01 01.cpp utils.o

02: 02.cpp utils.o
	$(CC) $(CFLAGS) -o 02 02.cpp utils.o

clean:
	rm -f 01 02 *.o

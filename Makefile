#The options –g and –Wall must be enabled in the Makefile
CFLAGS = -g -Wall 
CC = g++

objects = mt-collatz.o main.o

mt-collatz: $(objects)
	$(CC) -o mt-collatz $(objects)

main.o: main.cpp
mt-collatz.o: mt-collatz.cpp

.PHONY : clean
clean: 
	rm mt-collatz $(objects)
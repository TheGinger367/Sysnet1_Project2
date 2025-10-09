CFLAGS = -g -Wall -pthread
CC = g++

objects = mt-collatz.o main.o

mt-collatz: $(objects)
	$(CC) $(CFLAGS) -o mt-collatz $(objects)

main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp

mt-collatz.o: mt-collatz.cpp
	$(CC) $(CFLAGS) -c mt-collatz.cpp

.PHONY : clean
clean: 
	rm -f mt-collatz $(objects)

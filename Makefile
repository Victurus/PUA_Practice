CC = g++ 
CFLAGS = -g -std=c++11 -Wall

all: clean compile run

compile: main.o
	$(CC) $(CFLAGS) main.o -o main

main.o:
	$(CC) $(CFLAGS) -c main.cpp -o main.o

run:
	./main

clean:
	rm -rf *.o
	rm -f main
	rm -f read/*coded

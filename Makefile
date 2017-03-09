all: clean compile run

compile: main.o
	g++ -g -std=c++11 -O0 main.o -o main

main.o:
	g++ -g -std=c++11 -O0 -c main.cpp -o main.o

run:
	./main

clean:
	rm -rf *.o
	rm main

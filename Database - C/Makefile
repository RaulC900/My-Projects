all: tema1

build: main.o parse.o main
main.o: main.c
	gcc -g -Wall -c main.c
parse.o: parse.c parse.h
	gcc -g -Wall -c parse.c
data.o: data.c data.h
	gcc -g -Wall -c data.c
tema1: main.o parse.o data.o
	gcc -g -Wall main.o parse.o data.o -o tema1

clean:
	rm -rf tema1
	rm -rf *.o

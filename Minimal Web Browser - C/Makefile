all: tema2

build: main.o Stack.o Queue.o utils.o parse.o List.o PriorityQueue.o BrowserFunctions.o tema2
main.o: main.c
	gcc -g -Wall -c main.c
Stack.o: Stack.c Stack.h
	gcc -g -Wall -c Stack.c
Queue.o: Queue.c Queue.h
	gcc -g -Wall -c Queue.c
utils.o: utils.c utils.h
	gcc -g -Wall -c utils.c
parse.o: parse.c parse.h
	gcc -g -Wall -c parse.c
List.o: List.c List.h
	gcc -g -Wall -c List.c
PriorityQueue.o: PriorityQueue.c PriorityQueue.h
	gcc -g -Wall -c PriorityQueue.c	
BrowserFunctions.o: BrowserFunctions.c BrowserFunctions.h
	gcc -g -Wall -c BrowserFunctions.c -lm
tema2: main.o Stack.o Queue.o utils.o parse.o List.o BrowserFunctions.o PriorityQueue.o
	gcc -g -Wall main.o Stack.o Queue.o utils.o parse.o List.o BrowserFunctions.o PriorityQueue.o -o tema2 -lm
	rm -rf *.o

clean:
	rm -rf tema2
	rm -rf *.o

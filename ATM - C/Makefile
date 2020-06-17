all: atm

build: atm.o main.o str_parse.o atm
atm.o: atm.c atm.h
	gcc -g -Wall -c atm.c
main.o: main.c
	gcc -g -Wall -c main.c
str_parse.o: str_parse.c str_parse.h
	gcc -g -Wall -c str_parse.c
atm: atm.o atm.h str_parse.o str_parse.h main.o
	gcc -g -Wall main.o atm.o str_parse.o -o atm
run: 
	./atm
clean:
	rm -rf *.o atm

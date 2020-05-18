CFLAGS=-pthread -g -Wpedantic -Wall -Werror -pedantic-errors -std=c11

all:	list

list:	list.o main.o
	gcc $(CFLAGS) list.o main.o -o list

list.o:	list.c list.h
	gcc -c $(CFLAGS) list.c -o list.o

main.o:	main.c list.h
	gcc -c $(CFLAGS) main.c -o main.o

run:
	./list

clean:
	rm -v *.o list

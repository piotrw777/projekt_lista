FLAGS := -g -pthread -Wpedantic -Wall -Werror -pedantic-errors -std=c11

all:
	gcc -c list.c -o list.o
	gcc -c main.c -o main.o
	gcc $(FLAGS) main.o list.o -o list
	
	

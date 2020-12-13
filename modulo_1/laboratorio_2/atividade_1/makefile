# Makefile mais simples

all: matmat

matmat: matmat.o
	gcc -o matmat matmat.o -lpthread

matmat.o: matmat.c timer.h
	gcc -o matmat.o matmat.c -c -Wall

clean:
	rm -rf *.o *~ matmat


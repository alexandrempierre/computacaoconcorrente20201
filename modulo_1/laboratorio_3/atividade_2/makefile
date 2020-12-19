# Makefile mais simples

all: pi_series.out

pi_series.out: pi_series.o
	gcc -o pi_series.out pi_series.o -lpthread -Wall --pedantic -g

pi_series.o: pi_series.c timer.h
	gcc -o pi_series.o pi_series.c -c -Wall --pedantic -g

clean:
	rm -rf *.o *~ pi_series.out


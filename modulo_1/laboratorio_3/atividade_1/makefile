# Makefile mais simples

all: pi_series_seq.out

pi_series_seq.out: pi_series_seq.o
	gcc -o pi_series_seq.out pi_series_seq.o -Wall -lpthread --pedantic

pi_series_seq.o: pi_series_seq.c timer.h
	gcc -o pi_series_seq.o pi_series_seq.c -c -Wall -lpthread --pedantic

clean:
	rm -rf *.o *~ pi_series_seq.out


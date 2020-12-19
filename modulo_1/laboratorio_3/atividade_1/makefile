# Makefile mais simples

all: pi_series_seq.out

pi_series_seq.out: pi_series_seq.o
	gcc -o pi_series_seq.out pi_series_seq.o -Wall --pedantic

pi_series_seq.o: pi_series_seq.c
	gcc -o pi_series_seq.o pi_series_seq.c -c -Wall --pedantic

clean:
	rm -rf *.o *~ pi_series_seq.out


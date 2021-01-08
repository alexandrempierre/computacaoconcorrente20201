main:
	gcc -o main.out main.c function.o -std=c99 -lm -lpthread -lrt -Wall --pedantic
euclidean_norm: clean
	ln -s functions/euclidean_norm.c . 
	gcc -o function.o euclidean_norm.c -std=c99 -lm -c
trigonometric_id: clean
	ln -s functions/trigonometric_id.c .
	gcc -o function.o trigonometric_id.c -std=c99 -lm -c
clean:
	find . -maxdepth 1 -type l -delete
	rm *.o *.out 2> /dev/null &
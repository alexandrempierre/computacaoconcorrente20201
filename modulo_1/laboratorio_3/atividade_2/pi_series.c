#include <stdio.h>
#include <stdlib.h>

#include <pthread.h>
#include <math.h>

#include "timer.h"

long long int N; // quantidade de termos da série
size_t T; // quantidade de threads

double series_term (long long int k);

void *subseries_sum (void *arg) {
    size_t thread = (size_t) arg;
    double partial_sum, *partial_sum_ptr;

    partial_sum = 0.0;
    partial_sum_ptr = (double *) malloc(sizeof(double));
    if (partial_sum_ptr == NULL)
    {
        fprintf(stderr, "ERRO -- malloc\n");
        exit(2);
    } 

    for (long long int k = N - thread; k > 0; k -= T) {
        partial_sum += series_term(k);
    }
    *partial_sum_ptr = partial_sum;

    pthread_exit((void *) partial_sum_ptr);
}

int main(int argc, char const *argv[])
{
    pthread_t *tid;
    
    double pi, *partial_sum_ptr;
    double start, finish, elapsed;

    if (argc < 3) {
        fprintf(stderr, "Digite: %s <quantidade de termos> <quantidade de threads>\n", argv[0]);
        return 1;
    }

    sscanf(argv[1], "%lld", &N); // ler quantidade de termos dos argumentos de linha de comando
    sscanf(argv[2], "%lud", &T); // ler quantidade de threads dos argumentos de linha de comando

    tid = malloc(T * sizeof(pthread_t));
    if (tid == NULL) {
        fprintf(stderr, "ERRO -- malloc\n");
        return 2;
    }

    GET_TIME(start);

    pi = 0.0;

    // laço de criação de threads
    for (size_t thread = 0; thread < T; thread++) {
        if ( pthread_create(&tid[thread], NULL, subseries_sum, (void *) thread) ) {
            fprintf(stderr, "ERRO -- pthread_create\n");
            return 3;
        }
    }

    // laço que aguarda o fim das threads
    for (size_t thread = 0; thread < T; thread++) {
        if ( pthread_join(tid[thread], (void **) &partial_sum_ptr) ) {
            fprintf(stderr, "ERRO -- pthread_join\n");
            return 4;
        }
        pi += *partial_sum_ptr;
        free(partial_sum_ptr);
    }
    pi *= 4.0;

    GET_TIME(finish);
    elapsed = finish - start;
    
    printf("Valor obtido: %.15f\n", pi);
    printf("Diferença do valor obtido para M_PI: %.15f\n", M_PI > pi ? M_PI - pi : pi - M_PI);
    printf("Tempo gasto no cálculo: %f\n", elapsed);

    return 0;
}

double series_term (long long int k) {
    double term = 1.0 / (double) (2*k - 1);

    if (k % 2 == 0) {
        term = -term;
    }

    return term;
}

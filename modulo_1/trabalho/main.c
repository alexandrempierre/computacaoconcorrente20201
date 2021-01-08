#define _POSIX_C_SOURCE 199309L
//https://stackoverflow.com/questions/26769129/trying-to-use-clock-gettime-but-getting-plenty-of-undeclared-errors-from-ti

#include <stdio.h>
#include <stdlib.h>

#include <pthread.h>

#include <complex.h>
#include <string.h>

#include <time.h>
#include "timer.h"

/* Substituir header abaixo pelo da função cuja matriz jacobiana se quer calcular */
#include "function.h"
/**/

/* Variáveis globais que serão usadas por todas as threads */
double *gradient, eps;
int domain_dim;
int nthreads;
/**/

typedef struct {
    int thread;
    double complex *input_values;
} t_args;

double directional_derivative (int domain_dim, int direction_index, 
double complex input_values[], double eps);

void *gradient_entries (void *arg);

int main(int argc, char const *argv[]) {
    pthread_t *tid;
    t_args *args;
    double complex *input_values;
    double input_aux;
    double start, finish, elapsed; // time variables

    if (argc < 3) {
        fprintf(stderr, "Digite: %s <número de threads> <dimensão do domínio da função>\n", argv[0]);
        return 1;
    }

    /* Inicialização das variáveis e estruturas de dados */
    sscanf(argv[1], "%d", &nthreads);
    sscanf(argv[2], "%d", &domain_dim);

    tid = (pthread_t *) malloc(nthreads * sizeof(pthread_t));
    if ( tid == NULL ) {
        fprintf(stderr, "ERRO -- malloc\n");
        return 2;
    }

    // Alocação do ponto no qual a (derivada da) função será avaliada
    input_values = (double complex *) malloc(domain_dim * sizeof(double complex));
    if ( input_values == NULL ) {
        fprintf(stderr, "ERRO -- malloc\n");
        return 2;
    }
    
    // printf("Entre com os %d valores de entrada da f:\n", domain_dim);
    eps = 1.0;
    for (int i = 0; i < domain_dim; i++) {
        scanf("%lf", &input_aux);
        input_values[i] = input_aux;
        // Definindo um valor adequado para o eps que garanta que eps^2 ~ 0
        while ( (input_aux + eps*eps) - input_aux ) { eps /= 2.0; }
    }

    gradient = (double *) malloc(domain_dim * sizeof(double));
    if ( gradient == NULL ) {
        fprintf(stderr, "ERRO -- malloc\n");
        return 2;
    }
    

    /* criação de threads */
    GET_TIME(start); // instante em que a parte concorrente se inicia

    for (int thread = 0; thread < nthreads; thread++) {
        args = (t_args *) malloc(sizeof(t_args));
        args->thread = thread;
        args->input_values = (double complex *) malloc(domain_dim * sizeof(double complex));
        
        memcpy(args->input_values, input_values, domain_dim * sizeof(double complex));

        if ( pthread_create(&tid[thread], NULL, gradient_entries, (void *) args) ) {
            fprintf(stderr, "ERRO -- pthread_create\n");
            return 3;
        }
    }   
    
    /* Aguarda o fim de todas as threads pra garantir o preenchimento 
     * total da matriz jacobiana
     */
    for (int thread = 0; thread < nthreads; thread++) {
        if ( pthread_join(tid[thread], NULL) ) {
            fprintf(stderr, "ERRO -- pthread_join\n");
            return 5;
        }
    }

    GET_TIME(finish); // instante em que a parte concorrente acaba
    elapsed = finish - start;

    /* Exibição dos resultados */
    printf("Gradiente no ponto dado:\n");
    
    for (int i = 0; i < domain_dim; i++) {
        printf("%e ", gradient[i]);
    }
    printf("\n");
    

    /* Tempo */
    printf("\nTempo: %lf s\n", elapsed);
    
    // A linha abaixo foi para as medições
    // printf("trigonometric_id,%d,%d,%lf\n", domain_dim, nthreads, elapsed);

    /* Desalocação de memória */
    free(input_values);
    free(gradient);

    return 0;
}

double directional_derivative (int domain_dim, int direction_index, 
double complex input_values[], double eps) {
    double complex evaluated_f;
    double df;

    if (direction_index >= domain_dim) {
        puts("ERRO -- tentativa de derivar numa variavel de entrada que nao existe");
        exit(4);
    }
    
    input_values[direction_index] += eps*I;

    evaluated_f = f(domain_dim, input_values);
    df = cimag(evaluated_f) / eps;

    input_values[direction_index] = creal(input_values[direction_index]);

    return df;
}

void *gradient_entries (void *arg) {
    t_args *args = (t_args *) arg;
    double complex *input_values = args->input_values;
    int thread = args->thread;

    for (int i = thread; i < domain_dim; i += nthreads) {
        gradient[i] = directional_derivative(domain_dim, i, input_values, eps);
    }

    free(input_values);
    free(args);
    
    pthread_exit(NULL);
}
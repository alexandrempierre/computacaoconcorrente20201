#include <stdio.h>
#include <stdlib.h>

#include <pthread.h>

#include "timer.h"

double **malloc_square_matrix (int mat_dim);
double sample_uniform ();
void fill_square_matrix (
    double **matrix, int mat_dim, double (*generate_element)(int i, int j)
);
void free_matrix (double **matrix, int n_rows);
void print_square_matrix (double **matrix, int mat_dim, char *format);

typedef struct {
    int n_threads;
    int mat_dim;
    double **mat_a, **mat_b, **mat_prod;

    int first_row;
} t_args;

// calcula linhas da matriz produto
void *matrix_product (void *arg) {
    int i, j, k;
    t_args *args = (t_args *) arg;

    for (i = args->first_row; i < args->mat_dim; i += args->n_threads) {
        for (j = 0; j < args->mat_dim; j++) {
            args->mat_prod[i][j] = 0;
            
            for (k = 0; k < args->mat_dim; k++) {
                args->mat_prod[i][j] += args->mat_a[i][k] * args->mat_b[k][j];
            }
        }
    }

    pthread_exit(NULL);
}

int main (int argc, char *argv[]) {
    int n_threads, mat_dim; // parametros do programa
    double **mat_a, **mat_b, **mat_prod;

    int thread; // iterador
    double start, finish, initialization, concurrent, end; // variaveis de medida de tempo
    pthread_t *tid;
    t_args **args;

    if (argc < 2) {
        printf("ERRO -- argumentos insuficientes");
        exit(-1);
    }

    // obter a quantidade de threads
    sscanf(argv[1], "%d", &n_threads);

    // obter as dimensões da matriz
    sscanf(argv[2], "%d", &mat_dim);

    GET_TIME(start); // medir tempo para incialização das estruturas de dados

    // alocar identificador
    tid = (pthread_t *) malloc(sizeof(pthread_t) * n_threads);
    if (tid == NULL) {
        printf("ERRO -- malloc\n");
        exit(-1);
    }

    // alocar vetor de argumentos
    args = (t_args **) malloc(sizeof(t_args *) * n_threads);
    if (args == NULL) {
        printf("ERRO -- malloc\n");
        exit(-1);
    }

    // alocar matrizes
    mat_a = malloc_square_matrix(mat_dim);
    mat_b = malloc_square_matrix(mat_dim);
    mat_prod = malloc_square_matrix(mat_dim);

    // inicializar matrizes
    fill_square_matrix(mat_a, mat_dim, sample_uniform);
    fill_square_matrix(mat_b, mat_dim, sample_uniform);

    GET_TIME(finish); // fim da medida da inicialização de estruturas de dados
    initialization = finish - start;

    GET_TIME(start); // medida da parte concorrente

    // criar threads e disparar as tarefas
    for (thread = 0; thread < n_threads; thread++) {
        args[thread] = (t_args *) malloc(sizeof(t_args));
        
        args[thread]->n_threads = n_threads;
        args[thread]->mat_dim = mat_dim;

        args[thread]->mat_a = mat_a;
        args[thread]->mat_b = mat_b;
        args[thread]->mat_prod = mat_prod;

        args[thread]->first_row = thread;

        if ( pthread_create(&tid[thread], NULL, matrix_product, (void *)args[thread]) ) {
            printf("ERRO -- pthread_create\n");
            exit(-1);
        }
    }
    
    // aguadar o fim das threads
    for (thread = 0; thread < n_threads; thread++) {
        if ( pthread_join(tid[thread], NULL) ) {
            printf("Erro -- pthread_join\n");
            exit(-1);
        }
    }

    GET_TIME(finish); // fim da medida da parte concorrente
    concurrent = finish - start;

    // imprimir matrizes usadas e resultados
    // printf("Matriz A:\n");
    // print_square_matrix(mat_a, mat_dim, "%f ");

    // printf("\nMatriz B:\n");
    // print_square_matrix(mat_b, mat_dim, "%f ");

    // printf("\nMatriz Produto:\n");
    // print_square_matrix(mat_prod, mat_dim, "%f ");

    // printf("\n");
    
    GET_TIME(start); // medida de tempo da finalização do programa

    for (thread = 0; thread < n_threads; thread++) {
        free(args[thread]);
    }
    free(args);
    free(tid);
    free_matrix(mat_a, mat_dim);
    free_matrix(mat_b, mat_dim);
    free_matrix(mat_prod, mat_dim);

    GET_TIME(finish); // medida de tempo da finalização do programa
    end = finish - start;

    printf("%d Thread%s\n", n_threads, n_threads > 1 ? "s" : "");
    printf("Inicialização -- %.3f segundos\n", initialization);
    printf("Produto de matrizes -- %.3f segundos\n", concurrent);
    printf("Finalização -- %.3f segundos\n", end);
    printf("Tempo total -- %.3f\n", initialization + concurrent + end);
    
    return 0;
}

double **malloc_square_matrix (int mat_dim) {
    int i;
    double **matrix = (double **) malloc(sizeof(double *) * mat_dim);
    if (matrix == NULL) {
        printf("ERRO -- malloc");
        exit(-1);
    }
    
    for (i = 0; i < mat_dim; i++) {
        matrix[i] = (double *) malloc(sizeof(double) * mat_dim);
        if (matrix[i] == NULL) {
            printf("ERRO -- malloc");
            exit(-1);
        }
    }
    
    return matrix;
}

double sample_uniform (int i, int j) {
    return (double)rand() / (double)RAND_MAX;
}

void fill_square_matrix (
    double **matrix, int mat_dim, double (*generate_element)(int i, int j)
) {
    int i, j;

    for (i = 0; i < mat_dim; i++) {
        for (j = 0; j < mat_dim; j++) {
            matrix[i][j] = generate_element(i, j);
        }
    }
}

void free_matrix (double **matrix, int n_rows) {
    int i;

    for (i = 0; i < n_rows; i++) {
        free(matrix[i]);
    }
    
    free(matrix);
}

void print_square_matrix (double **matrix, int mat_dim, char *format) {
    int i, j;
    for (i = 0; i < mat_dim; i++) {
        for (j = 0; j < mat_dim; j++) {
            printf(format, matrix[i][j]);
        }
        printf("\n");
    }
}

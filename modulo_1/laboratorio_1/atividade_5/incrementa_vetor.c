#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NTHREADS 2

int* zeros;
int size;

// funcao executada pelas threads
void* inc_array (void* arg) {
    int start = *(int *) arg;
    
    int i;
    for (i = start; i < size; i+=NTHREADS) {
        zeros[i] += 1;
    }

    pthread_exit(NULL);
}

int main (int argc, char* argv[]) {
    pthread_t tid[NTHREADS];
    int start[NTHREADS];
    int thread;
    int i;

    // obtem o tamanho do vetor a ser incrementado e coloca numa variavel global
    sscanf(argv[1], "%d", &size);

    if (size <= 10 || size >= 100) { // verifica se o tamanho do vetor e valido
        printf("ERRO -- tamanho invalido para o vetor\n");
        exit(-1);
    }
    else { // aloca o vetor
         zeros = malloc(sizeof(int) * size);
         if (zeros == NULL) {
             printf("ERRO -- malloc\n");
         }
    }

    // inicializa o vetor
    for (i = 0; i < size; i++) {
        zeros[i] = 0;
    }

    // imprime valores iniciais do vetor
    for (i = 0; i < size; i++) {
        printf("%d\n", zeros[i]);
    }

    // cria as threads
    for (thread = 0; thread < NTHREADS; thread++) {
        start[thread] = thread;
        if ( pthread_create(&tid[thread], NULL, inc_array, (void *) &start[thread]) ) {
            printf("ERRO -- pthread_create\n");
        }
    }

    // aguarda o fim das threads
    for (thread = 0; thread < NTHREADS; thread++) {
        if ( pthread_join(tid[thread], NULL) ) {
            printf("Erro -- pthread_join\n");
        }
    }

    // quebra de linha para separar os valores iniciais do vetor dos valores finais
    printf("\n");
    
    // imprime valores do vetor depois do fim das threads
    for (i = 0; i < size; i++) {
        printf("%d\n", zeros[i]);
    }

    return 0;
}
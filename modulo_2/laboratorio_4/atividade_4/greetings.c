#include <stdio.h>
#include <stdlib.h>

#include <pthread.h>

#include <errno.h>

#define FALSE       0
#define TRUE        1
#define NTHREADS    4

/* Variáveis globais */
pthread_mutex_t mutex;
pthread_cond_t cond;
int tudo_bem, bom_dia;

void *thread_1 (void *arg) {
    puts("tudo bem?");

    pthread_mutex_lock(&mutex);
    tudo_bem = TRUE;
    if ( bom_dia ) {
        pthread_cond_broadcast(&cond);
    }
    pthread_mutex_unlock(&mutex);

    pthread_exit(NULL);
}

void *thread_2 (void *arg) {
    puts("bom dia!");

    pthread_mutex_lock(&mutex);
    bom_dia = TRUE;
    if ( tudo_bem ) {
        pthread_cond_broadcast(&cond);
    }
    pthread_mutex_unlock(&mutex);

    pthread_exit(NULL);
}

void *thread_3 (void *arg) {
    pthread_mutex_lock(&mutex);
    if ( !tudo_bem || !bom_dia ) {
        pthread_cond_wait(&cond, &mutex);
    }

    puts("até mais!");
    pthread_mutex_unlock(&mutex);

    pthread_exit(NULL);
}

void *thread_4 (void *arg) {
    pthread_mutex_lock(&mutex);
    if ( !tudo_bem || !bom_dia ) {
        pthread_cond_wait(&cond, &mutex);
    }

    puts("boa tarde!");
    pthread_mutex_unlock(&mutex);

    pthread_exit(NULL);
}

int main(int argc, char const *argv[]) {
    // int i;
    pthread_t threads[NTHREADS];

    /* Inicialização das variáveis de estado das threads */
    bom_dia = FALSE; tudo_bem = FALSE;

    /* Inicialização das variáveis de controle de lock e de condição */
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond, NULL);

    /* Criação das threads */
    pthread_create(&threads[0], NULL, thread_1, NULL);
    pthread_create(&threads[1], NULL, thread_2, NULL);
    pthread_create(&threads[2], NULL, thread_3, NULL);
    pthread_create(&threads[3], NULL, thread_4, NULL);

    /* Espera pelo fim de todas as threads */
    for (int i = 0; i < NTHREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    /* Desalocação das variáveis de controle de lock e de condição */
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);

    return 0;
}

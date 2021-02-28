#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <time.h>

#define N_THREADS 2

sem_t mutex, cond;
int bloqueadas = 0;

void barreira(int numThreads, int id) {
    sem_wait(&mutex);
    bloqueadas++;
    printf("thread %d: bloqueadas = %d\n", id, bloqueadas);
    if (bloqueadas < numThreads) {
        sem_post(&mutex);
        sem_wait(&cond);
        bloqueadas--;
        if (bloqueadas==0) {
            sem_post(&mutex);
        }
        else {
            sem_post(&cond);
        }
    } else {
        sem_post(&cond);
        bloqueadas--;
    }
}

void * tarefa (void * arg) {
    int id = * (int *) arg;
    int n = 10;
    while (--n) {
        printf("thread %d: mutex = %d, cond = %d\n", id, mutex, cond);
        barreira(N_THREADS, id);
    }
    printf("thread %d chegou ao fim\n",id);

    pthread_exit(NULL);
}

int main(int argc, char const *argv[]) {
    pthread_t t[N_THREADS];
    int id[N_THREADS];

    sem_init(&mutex, 0, 1);
    sem_init(&cond, 0, 1);

    for (int i = 0; i < N_THREADS; i++) {
        id[i] = i + 1;
        pthread_create(t + i, NULL, tarefa, (void *) (id + i));
    }

    pthread_exit(NULL);

    return 0;
}

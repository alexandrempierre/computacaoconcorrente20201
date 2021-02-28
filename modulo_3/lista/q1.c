#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

//variaveis globais
sem_t em, dorme, e;
int cont=0, n_sul=0, n_norte=0;

void espera () {
    sem_wait(&em);
    cont++;
    sem_post(&em);

    sem_wait(&dorme);
    cont--;

    if (cont > 0) sem_post(&dorme);
    else sem_post(&em);
}

void libera () {
    sem_wait(&em);
    if (cont > 0) sem_post(&dorme);
    else sem_post(&em);
}

void *carro_vindo_do_norte (void *arg) {
    sem_wait(&e);
    {
        while(n_sul > 0) {
            sem_post(&e);
            espera();
            sem_wait(&e);
        }
    
        n_norte++;
    }
    sem_post(&e);

    //atravessa a ponte
    sem_wait(&e);
    {
        n_norte--;
        
        if(n_norte == 0) libera();
    }
    sem_post(&e);

    pthread_exit(NULL);
}

void *carro_vindo_do_sul (void *arg) {
    sem_wait(&e);
    {
        while(n_norte > 0) {
            sem_post(&e);
            espera();
            sem_wait(&e);
        }

        n_sul++;
    }
    sem_post(&e);
    
    //atravessa a ponte
    
    sem_wait(&e);
    {
        n_sul--;
        
        if(n_sul == 0) libera();
    }
    sem_post(&e);

    pthread_exit(NULL);
}

int main(int argc, char const *argv[])
{
    sem_init(&em,0,1); 
    sem_init(&dorme,0,0); 
    sem_init(&e,0,1);
    return 0;
}

#include <semaphore.h>

//globais
sem_t em, par;
int cont=0;

//codigo das threads
void *T(void *args) {
    while(1) {
        //executa código que não depende do recurso...
        sem_wait(&em);
        
        cont++;
        
        if(cont!=2) {
            sem_post(&em);
            sem_wait(&par);
            sem_post(&par);
        } else {
            sem_post(&par);
        }
        
        //executa o código que usa o recurso...
        sem_wait(&par);
        cont--;
        if(cont==0) sem_post(&em);
        else sem_post(&par);
    }
}

int main(int argc, char const *argv[])
{
    sem_init(&em, 0, 1); 
    sem_init(&par,0,0);
    
    return 0;
}

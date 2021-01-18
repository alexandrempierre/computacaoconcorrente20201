#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>

#define TAM     100
#define FALSE   0
#define TRUE    1

int vetor[TAM], N, M, lendo, escrevendo, 
    escritoras_com_prioridade, escritoras_sem_prioridade, primeira_escrita;
pthread_mutex_t mutex;
pthread_cond_t cond_leitura, cond_escrita;
char **buffer_print_leitora;

double media ();
void buffer_vetor (int thread);

void *leitora (void *arg) {
    int thread, *id = (int *) arg;
    thread = *id;

    while (1) {
        /* Inicialização e sincronização com as escritoras */
        pthread_mutex_lock(&mutex);
        {
            printf("thread %d (leitora) quer ler\n", thread);
            while (escrevendo || escritoras_com_prioridade) {
                printf("thread %d (leitora) se bloqueou\n", thread);
                pthread_cond_wait(&cond_leitura, &mutex);
                printf("thread %d (leitora) se desbloqueou\n", thread);
            }
            lendo++;
            primeira_escrita = TRUE;
        }
        pthread_mutex_unlock(&mutex);

        /* Tarefa da thread leitora */
        buffer_vetor(thread);
        printf("thread %d (leitora) reportando...\n%s\n%s\nMédia: %lf\n", 
                thread, 
                "Valores no vetor:", 
                buffer_print_leitora[thread], 
                media()
            );

        /* Finalização */
        pthread_mutex_lock(&mutex);
        {
            printf("thread %d (leitora) terminou de ler\n", thread);
            if (--lendo == 0) {
                pthread_cond_signal(&cond_escrita);
            }
        }
        pthread_mutex_unlock(&mutex);

        sleep(1);
    }

    free(arg);
    pthread_exit(NULL);
}

void *escritora (void *arg) {
    int i, thread, *id = (int *) arg;
    thread = *id;

    while (1) {
        /* Inicialização e sincronização com as leitoras e outras escritoras */
        pthread_mutex_lock(&mutex);
        {
            printf("thread %d (escritora) quer escrever\n", thread);
            while (lendo || escrevendo) {
                if (lendo) {
                    escritoras_com_prioridade++;
                } else {
                    escritoras_sem_prioridade++;
                }
                printf("thread %d (escritora) se bloqueou\n", thread);
                pthread_cond_wait(&cond_escrita, &mutex);
                printf("thread %d (escritora) se desbloqueou\n", thread);
            }
            escrevendo++;

            if (primeira_escrita) {
                escritoras_com_prioridade += escritoras_sem_prioridade;
                escritoras_sem_prioridade = 0;
                primeira_escrita = FALSE;
            }

            if (escritoras_com_prioridade > 0) {
                escritoras_com_prioridade--;
            } else {
                escritoras_sem_prioridade--;
            }
        }
        pthread_mutex_unlock(&mutex);

        /* Tarefa da thread escritora */
        vetor[0] = thread; vetor[TAM-1] = thread;
        for (i = 1; i < TAM-1; i++) {
            vetor[i] = 2*thread;
        }

        /* Finalização */
        pthread_mutex_lock(&mutex);
        {
            printf("thread %d (escritora) terminou de escrever\n", thread);
            escrevendo--;
            pthread_cond_signal(&cond_escrita);
            pthread_cond_broadcast(&cond_leitura);
        }
        pthread_mutex_unlock(&mutex);

        sleep(1);
    }
    
    free(arg);
    pthread_exit(NULL);
}

int main (int argc, char const *argv[])
{
    int thread, *thread_id;
    pthread_t *tid;

    if (argc < 3) {
        fprintf(stderr, "Digite: %s <quantidade de leitores> <quantidade de escritores>\n", argv[0]);
        return 1;
    }
    
    sscanf(argv[1], "%d", &M); // leitoras
    if (M < 1) {
        fprintf(stderr, "ERRO -- número de threads leitoras deve ser estritamente positivo\n");
        return 2;
    }

    sscanf(argv[2], "%d", &N); // escritoras
    if (N < 1) {
        fprintf(stderr, "ERRO -- número de threads escritoras deve ser estritamente positivo\n");
        return 2;
    }

    tid = (pthread_t *) malloc( (N + M) * sizeof(pthread_t) );
    if ( tid == NULL ) {
        fprintf(stderr, "ERRO -- malloc -- tid\n");
        return 3;
    }

    thread_id = (int *) malloc( (N + M) * sizeof(int) );
    if ( thread_id == NULL ) {
        fprintf(stderr, "ERRO -- malloc -- thread_id\n");
        return 3;
    }

    buffer_print_leitora = (char **) malloc( M * sizeof(char *) );
    if ( buffer_print_leitora == NULL ) {
        fprintf(stderr, "ERRO -- malloc -- buffer_print_leitora\n");
        return 3;
    }

    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond_escrita, NULL);
    pthread_cond_init(&cond_leitura, NULL);

    lendo = 0; escrevendo = 0;
    escritoras_com_prioridade = 0, escritoras_sem_prioridade = 0, primeira_escrita = TRUE;

    // Criação das M threads leitoras
    for (thread = 0; thread < M; thread++) {
        buffer_print_leitora[thread] = (char *) malloc( 3*TAM * sizeof(char));
        if ( buffer_print_leitora[thread] == NULL ) {
            fprintf(stderr, "ERRO -- malloc -- buffer_print_leitora[%d]\n", thread);
            return 3;
        }

        thread_id[thread] = thread;

        if ( pthread_create(tid + thread, NULL, leitora, (void *) (thread_id + thread)) ) {
            fprintf(stderr, "ERRO -- pthread_create -- leitoras\n");
            return 4;
        }
    }
    
    // Criação das N threads escritoras
    for (thread = M; thread < M+N; thread++) {
        thread_id[thread] = thread;

        if ( pthread_create(tid + thread, NULL, escritora, (void *) (thread_id + thread)) ) {
            fprintf(stderr, "ERRO -- pthread_create -- escritoras\n");
            return 4;
        }
    }

    pthread_exit(NULL);

    return 0;
}

double media () {
    int s = 0, i;

    for (i = 0; i < TAM; i++) {
        s += vetor[i];
    }
    
    return (double) s / (double) TAM;
}

void buffer_vetor (int thread) {
    int i;
    char v[3];
    
    buffer_print_leitora[thread][0] = '\0';
    for (i = 0; i < TAM; i++) {
        sprintf(v, "%d ", vetor[i]);
        buffer_print_leitora[thread] = strcat(buffer_print_leitora[thread], v);
    }
}
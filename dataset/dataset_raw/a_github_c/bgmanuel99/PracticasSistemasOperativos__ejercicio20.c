#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <semaphore.h>
#include <string.h>

int buffer[10]={0,0,0,0,0,0,0,0,0,0};
sem_t semaforo;

void *fhilo1(void *arg){
    int i;

    printf("\nEstoy llenando el buffer \n");

    for(i = 0; i < 10; i++){
        sem_trywait(&semaforo);
        
        buffer[i] = i+1;
        sem_post(&semaforo);
    }

    sleep(random()%3);
    pthread_exit(NULL);
}
void *fhilo2(void *arg){
    int i;

    printf("\nLos valores del buffer son: \n");

    for(i = 0; i < 10; i++){
        sem_trywait(&semaforo); 
        printf("%d, ",buffer[i]);
        buffer[i] = 0;
        sem_post(&semaforo);
    }

    sleep(random()%3);
    printf("\n");

    for(i = 0; i < 10; i++){
        printf("%d, ",buffer[i]);
    }
    pthread_exit(NULL);
}

int main(int argc, char const *argv[])
{
    pthread_t hilo1,hilo2;
    time_t t;
    srandom(time(&t));

    sem_init(&semaforo,0,10);

    while(1){
        pthread_create(&hilo1,NULL, *fhilo1,NULL);
        pthread_create(&hilo2,NULL, *fhilo2,NULL);

        if(buffer[0] == 0) pthread_join(hilo1,NULL);
        else pthread_join(hilo2,NULL);
    }
    

    sem_destroy(&semaforo);

    return 0;
}

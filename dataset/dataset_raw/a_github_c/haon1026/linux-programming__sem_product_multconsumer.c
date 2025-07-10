

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define NUM 5
int queue[NUM];                        
sem_t blank_number;                     
sem_t product_number;                   
int i = 0;

void *product(void *arg)
{
    int i = 0;
    while(1)
    {
        sem_wait(&blank_number);                    
        queue[i] = rand() % 1000 + 1;              
        printf("-----Produce %d\n", queue[i]);                     

        sem_post(&product_number);     
        i = (i+1) % NUM;                    

        sleep(rand()%1);
    }
}

void *comsumer(void *arg)
{
    while(1)
    {
        sem_wait(&product_number);                 
        printf("Comsume:%lu queue[%d]=%d\n", pthread_self(), i, queue[i]);           
        queue[i] = 0;                                                 
        sem_post(&blank_number);     
        i = (i+1) % NUM;                                       
        
        sleep(rand()%2);
    }
}

int main()
{
    srand(time(NULL));
    pthread_t cid[5], pid;

    sem_init(&blank_number, 0, NUM);            
    sem_init(&product_number, 0, 0);            

    pthread_create(&pid, NULL, product, NULL);
    for(int i = 0; i < 5; i++)
    {
        pthread_create(&cid[i], NULL, comsumer, NULL);
    }

    pthread_join(pid, NULL);
    for(int i = 0; i < 5; i++)
    {
        pthread_join(cid[i], NULL);
    }

    sem_destroy(&blank_number);
    sem_destroy(&product_number);

    return 0;
}
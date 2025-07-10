

#define _XOPEN_SOURCE 500     
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

int counter;
pthread_rwlock_t rwlock;


void *thread_write(void *arg)
{
    int t;
    int i = (int)arg;
    while(1)
    {
        pthread_rwlock_wrlock(&rwlock);     
        t = counter;
        usleep(1000);       
        printf("write %d:%lu: counter=%d ++counter=%d\n", i, pthread_self(), t, ++counter);
        pthread_rwlock_unlock(&rwlock);
        usleep(10000);
    }
    return NULL;
}

void *thread_read(void *arg)
{
    int i = (int)arg;
    while(1)
    {
        pthread_rwlock_wrlock(&rwlock);     
        printf("read %d:%lu: counter=%d\n", i, pthread_self(), counter);
        pthread_rwlock_unlock(&rwlock);
        usleep(2000);
    }
    return NULL;
}

int main()
{
    pthread_t tid[8];
    pthread_rwlock_init(&rwlock, NULL);

    int i;
    for(i = 0; i < 3; i++)
        pthread_create(&tid[i], NULL, thread_write, (void*)i);
    
    for(i = 0; i < 5; i++)
        pthread_create(&tid[i+3], NULL, thread_read, (void*)i);
    
    for(i = 0; i < 8; i++)
        pthread_join(tid[i], NULL);

    pthread_rwlock_destroy(&rwlock);

    return 0;
}


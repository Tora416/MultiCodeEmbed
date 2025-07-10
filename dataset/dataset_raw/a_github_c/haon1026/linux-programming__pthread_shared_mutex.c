
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <pthread.h>

pthread_mutex_t mutex;  

void *fun(void *arg)
{
    srand(time(NULL));

    while (1)
    {
        pthread_mutex_lock(&mutex);     
        printf("hello ");
        sleep(rand()%3);    
        printf("world\n");
        pthread_mutex_unlock(&mutex);   
        sleep(rand()%3);
    }

    return NULL;
}

int main()
{
    srand(time(NULL));
    pthread_t tid;

    int ret = pthread_mutex_init(&mutex, NULL);     
    if(ret != 0)
    {
        fprintf(stderr, "pthread_mutex_init error:%s\n", strerror(ret));
        exit(1);
    }

    pthread_create(&tid, NULL, fun, NULL);
    while (1)
    {
        pthread_mutex_lock(&mutex);     
        printf("HELLO ");
        sleep(rand()%3);
        printf("WORLD\n");
        pthread_mutex_unlock(&mutex);   
        sleep(rand()%3);
    }
    pthread_join(tid, NULL);
    pthread_mutex_destroy(&mutex);      
    return 0;
}


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

int val1;
int val2;
pthread_mutex_t mutex1;
pthread_mutex_t mutex2;

void* fun1(void *arg)
{
    pthread_mutex_lock(&mutex1);
    printf("val1 = %d\n", val1);
    sleep(1);
    pthread_mutex_lock(&mutex2);
    val2 = 100;
    printf("val2 = %d\n", val2);
    pthread_mutex_unlock(&mutex2);
    pthread_mutex_unlock(&mutex1);

    return NULL;
}

void* fun2(void *arg)
{
    pthread_mutex_lock(&mutex2);
    printf("val2 = %d\n", val2);
    sleep(1);
    pthread_mutex_lock(&mutex1);
    val1 = 200;
    printf("val1 = %d\n", val1);
    pthread_mutex_unlock(&mutex1);
    pthread_mutex_unlock(&mutex2);
    return NULL;
}

int main()
{
    pthread_mutex_init(&mutex1, NULL);
    pthread_mutex_init(&mutex2, NULL);
    pthread_t tid1, tid2;

    pthread_create(&tid1, NULL, fun1, NULL);
    pthread_create(&tid2, NULL, fun2, NULL);

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    pthread_mutex_destroy(&mutex1);
    pthread_mutex_destroy(&mutex2);
    return 0;
}
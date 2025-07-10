
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

void *fun(void *arg)
{
    srand(time(NULL));

    while (1)
    {
        printf("hello ");
        sleep(rand()%3);    
        printf("world\n");
        sleep(rand()%3);
    }

    return NULL;
}

int main()
{
    srand(time(NULL));
    pthread_t tid;

    pthread_create(&tid, NULL, fun, NULL);
    while (1)
    {
        printf("HELLO ");
        sleep(rand()%3);
        printf("WORLD\n");
        sleep(rand()%3);
    }
    pthread_join(tid, NULL);
    return 0;
}
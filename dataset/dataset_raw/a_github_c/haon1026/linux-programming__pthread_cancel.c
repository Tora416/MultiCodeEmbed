

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <errno.h>

void* thread_fun(void *arg)
{   
    while(1)
    {
        printf("thread:pid = %d, tid = %lu\n", getpid(), pthread_self());
        sleep(1);
    }
    
    return NULL;
}

int main()
{
    pthread_t tid;
    int ret = pthread_create(&tid, NULL, thread_fun, NULL);
    if(ret != 0)
    {
        fprintf(stderr, "pthread_create error:%s\n", strerror(errno));
        exit(1);
    }

    printf("main:pid = %d, tid = %lu\n", getpid(), pthread_self());
    sleep(5);
    ret = pthread_cancel(tid);          
    if(ret != 0)
    {
        fprintf(stderr, "pthread_cancel error:%s\n", strerror(errno));
        exit(1);
    }
    
    while(1);

    return 0;    
}
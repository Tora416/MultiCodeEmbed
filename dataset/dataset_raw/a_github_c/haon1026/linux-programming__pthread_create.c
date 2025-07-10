

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void sys_err(const char *str)
{
    perror(str);
    exit(1);
}

void* thread_fun(void *arg)
{
    printf("thread:pid = %d, tid = %lu\n", getpid(), pthread_self());
    return NULL;
}

int main()
{
    printf("main:pid = %d, tid = %lu\n", getpid(), pthread_self());
    
    pthread_t tid;
    int ret = pthread_create(&tid, NULL, thread_fun, NULL);
    if(ret != 0)
        sys_err("pthread_create error");

    sleep(1);
    return 0;    
}
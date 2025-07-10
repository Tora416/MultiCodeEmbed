

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

struct thrd
{
    int var;
    char str[256];
};

void sys_err(const char *str)
{
    perror(str);
    exit(1);
}

void* thread_fun(void *arg)
{
    struct thrd *tval;
    tval = malloc(sizeof(struct thrd));
    tval->var = 100;
    strcpy(tval->str, "hello thread");

    return (void *)tval;
}

int main()
{
    pthread_t tid;
    int ret = pthread_create(&tid, NULL, thread_fun, NULL);
    if(ret != 0)
        sys_err("pthread_create error");
    
    struct thrd *retval;
    ret = pthread_join(tid, (void**)&retval);
    if(ret != 0)
        sys_err("pthread join error");

    printf("child thread exit with var = %d, str = %s\n", retval->var, retval->str);

    pthread_exit(NULL);
}
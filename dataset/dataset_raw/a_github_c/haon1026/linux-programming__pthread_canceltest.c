

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <errno.h>

void* thread_fun1(void *arg)
{   
    printf("thread 1 return\n");
    return (void*)111;
}

void* thread_fun2(void *arg)
{   
    printf("thread 2 return\n");
    pthread_exit((void*)222);
}

void* thread_fun3(void *arg)
{   
    

    

    
   
    return (void*)666;
}

int main()
{
    pthread_t tid;
    void *retval = NULL;

    pthread_create(&tid, NULL, thread_fun1, NULL);
    pthread_join(tid, &retval);
    printf("thread 1 exit code = %d\n\n", (int)retval);

    pthread_create(&tid, NULL, thread_fun2, NULL);
    pthread_join(tid, &retval);
    printf("thread 2 exit code = %d\n\n", (int)retval);

    pthread_create(&tid, NULL, thread_fun3, NULL);
    sleep(3);
    pthread_cancel(tid);
    pthread_join(tid, &retval);
    printf("thread 3 exit code = %d\n\n", (int)retval);     

    return 0;    
}
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <pthread.h> 











void *myThreadFun(void *vargp) 
{ 
    sleep(1); 
    printf("Printing GeeksQuiz from Thread \n");
    return NULL; 
} 

int main() 
{ 
    pthread_t thread_id; 
    printf("Before Thread\n"); 
        printf("ThreadId is %ld\n",thread_id);  
    pthread_create(&thread_id, NULL, &myThreadFun, NULL); 
    pthread_join(thread_id, NULL); 
    printf("After Thread\n"); 
    exit(0); 
}


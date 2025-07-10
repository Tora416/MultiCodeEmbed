#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pthread.h>

pthread_mutex_t my_lock1, my_lock2, my_lock_main;
pthread_mutexattr_t attr;

void *func1 (void *arg);
void *func2 (void *arg);

int aux[100];

void *func1 (void *arg){
    printf("He entrado en la func1\n");
    if (pthread_mutex_init(&my_lock1, NULL) != 0) { 
        printf("\nThread 1 mutex init has failed\n"); 
        return 1; 
    }

    pthread_mutex_lock(&my_lock1);



    printf("Soy el mutex thread y voy a introducir en aux todos 1\n");
    for(int i = 0; i < 100; i++){
        aux[i]=1;
    }

    printf("Thread 1:   El nuevo valor de aux es:\n");

    for(int i = 0; i<100 ;i++){
        printf("%d, ",aux[i]);
    }

    pthread_mutex_unlock(&my_lock1);
    pthread_exit(NULL);
}
 
void *func2(void *arg){
    printf("\nHe entrado en la func2\n");
        if (pthread_mutex_init(&my_lock2, NULL) != 0) { 
            printf("\nThread 2 mutex init has failed\n"); 
            return 1;
        }

        pthread_mutex_lock(&my_lock2);

        printf("Soy el mutex thread 2 y voy a introducir en aux todos 2\n");

        for(int i = 0; i < 100; i++){
            aux[i]=2;
        }
        
        printf("Thread 2:   El nuevo valor de aux es:\n");

        for(int i = 0; i<100 ;i++){
            printf("%d, ",aux[i]);
        }

        pthread_mutex_unlock(&my_lock2);
    
    pthread_exit(NULL);
}

int main(int argc, char *argv[]){
    if (pthread_mutex_init(&my_lock_main, NULL) != 0) { 
        printf("\n Thread main mutex init has failed\n"); 
        return 1; 
    }
    
    pthread_attr_init(&attr);

    pthread_create(&my_lock1, &attr, func1, NULL);
    sleep(5);
    pthread_create(&my_lock2, &attr, func2, NULL);

    sleep(10);
    
    if(pthread_mutexattr_destroy(&my_lock_main) == 0){
        printf("\nSe ha destruido el main thread\n");
    }
}
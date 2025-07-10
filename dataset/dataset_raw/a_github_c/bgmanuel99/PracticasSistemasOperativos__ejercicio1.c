#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void *func1 (void*);
void *func2 (void*);

pthread_t thread1, thread2, thmain;
pthread_attr_t attr;
pthread_mutex_t mutex;

int num1;
int num2;


void *func1 (void *arg){
    
    int suma = 1;
    int size=(int) arg;
    for(int i = 1; i < size; i++){
        suma = suma * (int) arg;
        arg--;
    }
    printf("Soy el thread 1 y estoy calculando el factorial de %d que es: %d \n", size, suma);
    pthread_exit(NULL);
}

void *func2 (void *arg){
    int err;
    if(err = pthread_join(thread1, NULL)){
        printf("Error al esperar a thread1 \n ");
    }else{
        int suma = 1;
        int size=(int) arg;
        for(int i = 1; i < size; i++){
            suma = suma * (int) arg;
            arg--;
        }
        printf("Soy el thread 2 y estoy calculando el factorial de %d que es: %d \n", size, suma);
    }
    pthread_exit(NULL);
}

int main(void){
    thmain = pthread_self();
    
    pthread_attr_init(&attr);

    printf("Soy la funcion main y voy a lanzar los dos threads \n");

    pthread_create(&thread1, &attr, func1, 4);
    pthread_create(&thread2, &attr, func2, 5);

    sleep(2);

    printf("Soy main: he lanzado los dos threads y termino\n");

    pthread_exit(NULL);
}
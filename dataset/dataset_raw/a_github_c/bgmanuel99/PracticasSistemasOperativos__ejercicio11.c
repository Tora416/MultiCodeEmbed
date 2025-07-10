#include <pthread.h> 
#include <stdio.h> 
#include <stdlib.h>

pthread_mutex_t count_mutex;
pthread_cond_t count_threshold_cv;
int buffer[10]={0,0,0,0,0,0,0,0,0,0};
void *productor(void *arg){
    int i = 0;
    printf("Lleno el buffer para mi consumidor\n");
    pthread_mutex_lock(&count_mutex); 
    for(i; i < 10;i++ ){
        buffer[i]=i+1;
    }
    printf("He terminado y permito a mi consumidor leer el buffer\n");
    pthread_cond_signal(&count_threshold_cv);
    pthread_mutex_unlock(&count_mutex);
    sleep(1);
    pthread_exit(NULL);
}

void *consumidor(void *arg){
int i = 0;
    printf("Voy a esperar a que se llenen los datos\n");
    pthread_mutex_lock(&count_mutex);
    pthread_cond_wait(&count_threshold_cv, &count_mutex); 
    printf("Voy a leer los datos y limpiar el buffer\n");
    for(i; i < 10;i++ ){
 
        printf("%d, ",buffer[i]);
        buffer[i]=0;
        pthread_mutex_unlock(&count_mutex);
    }
    printf("\n");
    sleep(2);
    pthread_exit(NULL);
}


int main(int argc, char const *argv[])
{
    pthread_t hilo1,hilo2;
    pthread_attr_t attr;

    pthread_mutex_init(&count_mutex, NULL);   
    pthread_cond_init (&count_threshold_cv, NULL);

    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
    while(1){
        pthread_create(&hilo1,&attr, *productor,NULL);
        pthread_create(&hilo2,&attr, *consumidor,NULL);
        pthread_join(hilo1,NULL);
        pthread_join(hilo2,NULL);

    }
    pthread_attr_destroy(&attr);   
    pthread_mutex_destroy(&count_mutex);   
    pthread_cond_destroy(&count_threshold_cv);   
    pthread_exit (NULL);
    return 0;
}

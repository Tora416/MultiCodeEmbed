



#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <errno.h>
#include <semaphore.h>

#define n 3                                     

int v[n];                                       
int indiceConsumicion = 0;                      
int indiceProduccion = 0;                       
int hebraProductor = 0;                         
int hebraConsumidor = 0;                        

sem_t mutex;                                    
sem_t full;                                     
sem_t empty;                                    

void producirDato(int numero){                  
    v[indiceProduccion] = numero;               
    indiceProduccion = (indiceProduccion +1)%n; 
    for(int i=0; i<n; i++){                     
            printf("|%d", v[i]);
    }
    printf("|");
}

int consumirDato(){                                 
    int numConsumido= v[indiceConsumicion];         
    v[indiceConsumicion] = '\0';                    
    indiceConsumicion = (indiceConsumicion +1)%n;   
        for(int i=0; i<n; i++){                     
            printf("|%d", v[i]);
        }
    printf("|");
    return numConsumido;                            
}

void * productor(){                                         
    sem_wait(&empty);                                       
    sem_wait(&mutex);                                       
    hebraProductor++;                                       
    int numero = rand()%101;                                
    producirDato(numero);                                   
    printf("---->Productor %d, Dato %d\n",hebraProductor, numero);
    sem_post(&mutex);                                       
    sem_post(&full);                                        
    
    pthread_exit(NULL);                                     
}

void * consumidor(){                                        
    sem_wait(&full);                                        
    sem_wait(&mutex);                                       
    hebraConsumidor++;                                      
    int numero = consumirDato();                            
    printf("---->Consumidor %d, Dato: %d\n", hebraConsumidor, numero);
    sem_post(&mutex);                                       
    sem_post(&empty);                                       
    
    pthread_exit(NULL);                                     
}

int main(){
    srand(time(NULL));                  

    sem_init(&mutex, 0, 1);             
    sem_init(&full, 0, 0);              
    sem_init(&empty, 0, n);             


    pthread_t threadProductor[3];       
    pthread_t threadConsumidor[3];      

    for (int i=0; i<3; i++){
        if(pthread_create(&threadProductor[i], NULL, productor, NULL)){                         
            printf("Error, no se ha podido crear la hebra. Codigo de error %d\n", errno);
            exit(EXIT_FAILURE);
        }
    }

    for (int i=0; i<3; i++){                                                                    
        if(pthread_create(&threadConsumidor[i], NULL, consumidor, NULL)){
            printf("Error, no se ha podido crear la hebra. Codigo de error %d\n", errno);
            exit(EXIT_FAILURE);
        }
    }
    
    for (int i=0; i<3; i++){
        if (pthread_join(threadProductor[i], NULL)){                                            
            printf("Error, no se ha podido recoger la hebra. Codigo de error %d\n", errno);
            exit(EXIT_FAILURE);
        }
    }

    for (int i=0; i<3; i++){
        if (pthread_join(threadConsumidor[i], NULL)){                                           
            printf("Error, no se ha podido recoger la hebra. Codigo de error %d\n", errno);
            exit(EXIT_FAILURE);
        }
    }
    
    for(int i=0; i<n; i++){                                     
        printf("Valor %d del buffer: %d\n", i+1, v[i]);
    }
    exit(EXIT_SUCCESS);                                         
}
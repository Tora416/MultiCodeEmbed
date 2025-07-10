






#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

void * aleatorio();

int main(){

    int n = 2;
    float total = 0, * subtotal;
    pthread_t hilos[n];

    for (int i = 0; i < n; i++){ pthread_create(&hilos[i], NULL, (void *) aleatorio, NULL); } 
    

    for (int i = 0; i < n; i++){
        
       pthread_join(hilos[i], (void **) &subtotal); 
       
       printf("Valor recibido: %f\n", *subtotal); 
       total = total + *subtotal; 
    }
    printf("la suma del total es: %f\n", total);

    exit(EXIT_SUCCESS);
     
}    

void * aleatorio(){

    float f1 = drand48()*10, f2 = drand48()*10;
    float * f3 = calloc(1, sizeof(float));
    *f3 = f1+f2;
    printf("%f + %f = %f\n", f1, f2, *f3);

    pthread_exit((void *) f3); 
    
    
}
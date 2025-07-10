






#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

void * cuentaLineas(void * fichero);

int main(int argc, char * argv[]){

    int nHilos = argc-1; 
    int total = 0; 
    int * nLineas=0;
    pthread_t hilos[nHilos];

    for (int i = 0; i < nHilos; i++){ pthread_create(&hilos[i], NULL, cuentaLineas, (void*) argv[i+1]); } 
    

    for (int i = 0; i < nHilos; i++) {

        pthread_join(hilos[i], (void**) &nLineas); 

        printf("El fichero %s tiene %i lineas\n", argv[i+1], *nLineas);

        total += *nLineas; 
    }

    printf("Entre todos los ficheros suman %i lineas\n", total);
    
}

void * cuentaLineas(void * fichero){

    printf("contando el fichero: %s\n", fichero);

    int * nLineas = malloc(sizeof(int)); 

    FILE * f = fopen(fichero, "r"); 

    *nLineas = 0; 

    char s[200]; 

    while(fgets(s, 200, f)){ *nLineas = *nLineas + 1; } 
        
    pthread_exit((void *) nLineas); 

}
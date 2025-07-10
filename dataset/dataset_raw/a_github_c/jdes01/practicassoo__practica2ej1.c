










#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>


void * generarNumeros(){

    int * z = malloc(sizeof(int)); 

    int x = rand() % 10;
    printf("x = %i \n", x);

    int y = rand() % 10;
    printf("y = %i \n", y);

    *z = x + y;

    printf("x + y = %i \n", *z);

    pthread_exit(z);
}


int main(int argc, char const *argv[]){

    srand (time(NULL));

    int nHebras = atoi(argv[1]);

    pthread_t thread[nHebras]; 

    int *numero, suma=0; 

    for (int i = 0; i < nHebras; i++){
   
        if( pthread_create( &(thread[i]), NULL, (void*) generarNumeros, NULL ) != 0 ){ 

            fprintf(stderr, "Error al crear la hebra");         
            exit(EXIT_FAILURE);                                 
        }
    }


    for (int i = 0; i < nHebras; i++){
   
        if( pthread_join( thread[i], (void **) &numero ) != 0 ){ 

            fprintf(stderr, "Error al usar join");         
            exit(EXIT_FAILURE);                  
        }

        suma = suma + *numero;
    }
    
    printf("%i", suma);

    return 0;
}


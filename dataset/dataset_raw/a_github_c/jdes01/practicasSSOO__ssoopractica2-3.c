



#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <errno.h>

typedef struct {        
         
  int *vector;          
  int hebras;           
  int i;                
  
} Vector;


void rellenaVector(int *vector){        

    srand(time(NULL));   

    for (int i = 0; i < 10; ++i){ vector[i] = ((rand()%9)+1); }
}

void imprimeVector (int *vector){       

    printf("El vector es:\n");
    printf("| ");

    for (int i = 0; i < 10; ++i){ printf("%d | ",vector[i]); }

    printf("\n");
}


void * sumaVector (void* v){            

    int *suma = malloc(sizeof(int));    
    *suma = 0;                          
    
    Vector *estructura;                 
    estructura = (Vector*) v;           
    

    if(estructura->hebras == 2){                                    

        for(int j=estructura->i; j<(estructura->i)+5; j++){         

            *suma = *suma + estructura->vector[j];
        }

        estructura->i = estructura->i + 5;
        pthread_exit((void**)suma);                                 
    }


    else{                                                           
        
        for(int j=estructura->i; j<(estructura->i)+2; j++){         
            
            *suma = *suma + estructura->vector[j];
        }

        estructura->i = estructura->i + 2;
        pthread_exit((void**)suma);                                 
    }

}


int main(int argc, char const *argv[]){
  
    Vector *v = malloc(sizeof(Vector));                 
    
    if (argc != 2){                                     
        
        printf("Error, llame al programa asi:\n");
        printf("./ej3 2 o /ej3 5\n");

        exit(EXIT_FAILURE);
    }

    v->hebras = atoi(argv[1]);                          
    v->i = 0;                                           

    if (v->hebras != 2 && v->hebras != 5){              
        
        printf("Error, llame al programa asi:\n");
        printf("./ej3 2 o /ej3 5\n");

        exit(EXIT_FAILURE);
    }
    
    v->vector = (int *)malloc (10*sizeof(int));         
    rellenaVector(v->vector);                           
    imprimeVector(v->vector);                           

    pthread_t thread[v->hebras];                        
    int *sumaLinea, suma = 0;                           
    
    printf("Se pasaran a crear %d hebras para sumar los valores del vector\n", v->hebras);

    for (int i = 0; i < v->hebras; i++){                
        
        if(pthread_create(&(thread[i]), NULL, (void*) sumaVector, (void*) v)){

            printf("Error en la creacion de la hebra. Codigo de error %d\n", errno);

            exit(EXIT_FAILURE);
        }

        if(pthread_join(thread[i], (void**) &sumaLinea)){

            printf("Error al esperar la hebra. Codigo de error %d\n", errno);

            exit(EXIT_FAILURE);
        } 

        suma = suma + *sumaLinea;                       
    }

    printf("La suma de los numeros de todos los valores es: %d\n", suma);

    exit(EXIT_SUCCESS);
}
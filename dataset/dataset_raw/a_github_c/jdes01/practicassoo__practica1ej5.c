








#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>

int variableGlobal = 0;

int main(){

    int n=5, status;

    printf("Padre con ID %d \n", getpid());
    printf("\n");

    for (int i=0; i<n; i++){
        
        switch (fork()){ 
        
        case -1:

            printf("Error en la creación \n");
            exit(EXIT_FAILURE);
        
        case 0:

            printf("Hijo %d con ID %d, padre: %d \n", i+1, getpid(), getppid());

            variableGlobal++;
            printf("%i\n", variableGlobal);

            exit(EXIT_SUCCESS); 

        default:

            printf("Esperando hijo numero %d \n", i+1);
            wait(&status); 
            printf("Hijo %d termindo con ID %d, codigo de salida: %d \n", i+1, getpid(), WEXITSTATUS(status)); 
            printf("\n");

        }

        
    } 

    printf("%i\n", variableGlobal);

    return 0;
}
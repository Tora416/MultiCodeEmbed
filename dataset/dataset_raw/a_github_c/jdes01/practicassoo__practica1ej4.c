








#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char * argv[]){

    int status;

    printf("Soy el proceso %d\n", getpid());

    for (int i = 0; i < argc - 1; i++){


        switch (fork()){

            case -1:

                    printf("ERROR");
                    exit(EXIT_FAILURE);
                    break;

            case 0: 

                    printf("soy el hijo numero %d; mi padre es el proceso: %d\n", getpid(), getppid); 

                        printf(" %i \n", factorial( atoi(argv[i+1]) ) );
                    exit(EXIT_SUCCESS);
                
                    break;

            default:

                    wait(&status); 
        }

    }

    return 0;
}


int factorial(int n){ 

  int resultado = 1;

  for (int i = n; i > 0; i--) {

    resultado *=i;
  }
  
  return resultado;
}
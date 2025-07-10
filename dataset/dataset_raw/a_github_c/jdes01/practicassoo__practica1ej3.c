





#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char * argv[]){

    switch (fork()){

        case -1:

                printf("ERROR");
                exit(EXIT_FAILURE);
                break;

        case 0: 

                printf("soy el hijo numero %d; mi padre es %d\n", getpid(), getppid); 
                execlp(argv[1], argv[1], NULL);
                exit(EXIT_SUCCESS);
                
                break;
    }

    
    switch (fork()){

        case -1:

                printf("ERROR");
                exit(EXIT_FAILURE);
                break;

        case 0: 

                printf("soy el hijo numero %d; mi padre es %d\n", getpid(), getppid); 
                execvp(argv[2], argv+2);
                exit(EXIT_SUCCESS);
                break;
    }


    return 0;
}
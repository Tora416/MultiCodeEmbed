



#include <stdlib.h>
#include <stdio.h>
#include <unistd.h> 
#include <sys/types.h> 
#include <errno.h> 
#include <sys/wait.h> 

int main(){

        switch ( fork() ){

        case -1: 
            perror("fork error:\n");
            fprintf(stderr, "errno:  %i\n", errno); 
            exit(EXIT_FAILURE);
            break;

        case 0: 
            printf("soy un proceso hijo con PID: %i; el PID de mi proceso padre es: %i\n", getpid(), getppid());
            break;

        default:
            sleep(10);
            exit(EXIT_FAILURE);
        }

}
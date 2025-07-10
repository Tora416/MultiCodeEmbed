



#include <stdlib.h>
#include <stdio.h>
#include <unistd.h> 
#include <sys/types.h> 
#include <errno.h> 
#include <sys/wait.h> 


int main(int argc, char * argv[]){

    int status;
    pid_t pid[2]; 

    switch ( fork() ){

            case -1: 
                perror("fork error:\n");
                fprintf(stderr, "errno:  %i\n", errno); 
                exit(EXIT_FAILURE);
                break;

            case 0: 
                printf("soy un proceso hijo con PID: %i; el PID de mi proceso padre es: %i\n", getpid(), getppid());
                
                
                
                exit(EXIT_SUCCESS); 
            }

    switch ( fork() ){

            case -1: 
                perror("fork error:\n");
                fprintf(stderr, "errno:  %i\n", errno); 
                exit(EXIT_FAILURE);
                break;

            case 0: 
                printf("soy un proceso hijo con PID: %i; el PID de mi proceso padre es: %i\n", getpid(), getppid());
                execlp("open", "open", "-t", argv[1], argv[2], NULL); 
                exit(EXIT_SUCCESS); 
            }

    pid[0]=wait(&status);
    pid[1]=wait(&status);


        
}



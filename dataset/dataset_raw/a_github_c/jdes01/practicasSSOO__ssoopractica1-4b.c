






#include <stdlib.h>
#include <stdio.h>
#include <unistd.h> 
#include <sys/types.h> 
#include <errno.h> 
#include <sys/wait.h> 

int main(int argc, char * argv[]){

    int n;

    int status;
    pid_t pid; 

    for (int i = 1; i < argc; i++){
 
        switch ( fork() ){
 
            case -1: 
                perror("fork error:\n");
                fprintf(stderr, "errno:  %i\n", errno); 
                exit(EXIT_FAILURE);

            case 0: 
                printf("soy un proceso hijo con PID: %i; el PID de mi proceso padre es: %i\n", getpid(), getppid());
                execlp("./a.out", "./a.out", argv[i], NULL);                
                exit(EXIT_SUCCESS); 
        }
 
        pid=wait(&status);
    }

   pid=wait(&status);
}


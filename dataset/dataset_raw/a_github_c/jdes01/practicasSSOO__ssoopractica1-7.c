







#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h> 
#include <sys/types.h> 
#include <errno.h> 
#include <sys/wait.h> 

void tratarSennal (int signo) { printf("recibida señal tratada por hijo"); }

int main(void){

    pid_t pid, pidHijo;
    int status, o=0;

    switch (pid) {

    case -1:

        exit(EXIT_FAILURE);
        break;

    case 0:

        signal(SIGUSR1, tratarSennal);

        for (int i = 0; i < 5; i++) pause();
        
        exit(EXIT_SUCCESS);
        break;    
    
    default:

        for (int i = 0; i < 5; i++){

            sleep(1);
            kill(pid,SIGUSR1);
        }

        pidHijo=wait(&status);
        break;
    }
}














#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

void tratarSignal() { printf("Señal recibida\n"); }

int main(){

    pid_t pid;

    printf("Soy %d el padre de todos\n", getpid()); 

    pid = fork();

    switch(pid){


        case -1: 

            printf("Error al crear el proceso hijo\n"); 
            exit(EXIT_FAILURE);

        case 0:

            signal(SIGUSR1, tratarSignal);      

            printf("Soy %d el hijo del proceso: %d\n", getpid(), getppid()); 

            for (int i = 0; i < 5; i++){      
        
                pause();
            }

            sleep(10);


        default: 

            printf("Esperando a que acabe mi hijo\n");

            for (int i = 0; i < 5; i++){ 
      
                sleep(3);
                kill(pid, SIGUSR1);
            }

            sleep(3);
            kill(pid, SIGKILL);
    }
   
  exit(EXIT_SUCCESS); 
}
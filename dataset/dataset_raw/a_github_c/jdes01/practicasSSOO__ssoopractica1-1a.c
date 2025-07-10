


#include <stdlib.h>
#include <stdio.h>
#include <unistd.h> 
#include <sys/types.h> 
#include <errno.h> 
#include <sys/wait.h> 

int main(){

    int n, status;
    pid_t pid; 

    printf("introduce el numero de procesos:\n");
    scanf("%i", &n);

    for (int i = 0; i < n; i++){

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
    }

    for (int i = 0; i < n; i++){

        pid = wait(&status); 
        
        

        if (pid > 0){ 
        
            if      (WIFEXITED(status))   printf("1 el hijo %i ha sido finalizado con la señal %i\n", pid, WEXITSTATUS(status));
            else if (WIFSIGNALED(status)) printf("2 el hijo %i ha sido finalizado con la señal %i\n", pid, WTERMSIG(status));
            else if (WIFSTOPPED(status))  printf("3 el hijo %i ha sido finalizado con la señal %i\n", pid, WSTOPSIG(status));
        
        }
        else{ 
            printf("fallo en la invocacion\n");
            exit(EXIT_FAILURE);
        }
         
    }
    
    exit(EXIT_SUCCESS);

}






#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h> 
#include <sys/types.h> 
#include <errno.h> 
#include <sys/wait.h> 

void ring (int signo) { printf("RING\n"); }

void funcion(int segundos){ 

    alarm(segundos); 
    pause(); 
    }

int main(){

    signal(SIGALRM, ring); 

    printf("Alarma en 5 segundo\n");
    funcion(5); 

    printf("Alarma en 3 segundo\n");
    funcion(3);

    for (int i = 0; i < 90; i++){

        printf("Alarma en 1 segundo\n");
        funcion(1);

        printf("TIMBRAZOS: %d\n", i+1);
        
        if (i==3) kill(getpid(),9);
        
    }

    return 0;
    
}
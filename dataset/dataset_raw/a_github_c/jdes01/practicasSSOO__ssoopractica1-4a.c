






#include <stdlib.h>
#include <stdio.h>
#include <unistd.h> 
#include <sys/types.h> 
#include <errno.h> 
#include <sys/wait.h> 

int factorial(int n);

int main(int argc, char * argv[]){

    int status;
    pid_t pid; 

    int n=0;

    for (int i = 0; i < argc-1; i++){

        switch ( fork() ){

            case -1: 
                perror("fork error:\n");
                fprintf(stderr, "errno:  %i\n", errno); 
                exit(EXIT_FAILURE);

            case 0: 
                printf("soy un proceso hijo con PID: %i; el PID de mi proceso padre es: %i\n", getpid(), getppid());
                sleep(1);
                n = atoi(argv[i+1]);
                printf("el factorial de %i es %i\n", n, factorial(n));
                sleep(1);
                exit(EXIT_SUCCESS); 
        }

        pid=wait(&status);
    }

    
}

int factorial(int n){

   int fact=1;

   if( n<0 ) return 0;

   if(n==0) return 1;

   for (int i = 1; i <= n; ++i) {fact = fact*i;} 
      
   return fact;
   
}
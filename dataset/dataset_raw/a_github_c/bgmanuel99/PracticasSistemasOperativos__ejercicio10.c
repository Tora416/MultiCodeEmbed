#include <sys/types.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

int main(int argc, char *argv[]){
    pid_t pid1;
    int status1=0,status2=0;
    int my_pipe[2];


    if (pipe(my_pipe)==-1){ 
        fprintf(stderr, "Pipe Failed" ); 
        return 1; 
    } 
    

    if((pid1=fork())==0){
        
        close(my_pipe[0]);
        printf("Child %d\n", getpid());

        char buffer[240];
        strcpy(buffer,"Envio este mensaje a mi padre usando las pipes aprendidas en la practica 3\n");
        write(my_pipe[1],&buffer,sizeof(buffer));
        exit(EXIT_SUCCESS);
        
    }else{
        
            printf("Father%d\n", getpid());

            waitpid(pid1,&status1,2);
            close(my_pipe[1]);

            char buffer[240];
            
            
            read(my_pipe[0],buffer,sizeof(buffer));
            printf(buffer);
    }
    return 0;
}
#include <sys/types.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

    int Par[10];
    int Impar[10];

int main(int argc, char *argv[]){
    pid_t pid1, pid2;
    int status1=0,status2=0;
    int my_pipe[2];
    int my_pipe2[2];


    if (pipe(my_pipe2)==-1){ 
        fprintf(stderr, "Pipe Failed" ); 
        return 1; 
    } 
    if (pipe(my_pipe)==-1){ 
        fprintf(stderr, "Pipe Failed" ); 
        return 1; 
    } 
    

    if((pid1=fork())==0){
        
        close(my_pipe[0]);
        printf("Child %d\n", getpid());
        int impar=1;
        for(int i=0;i<10;i++){
            Impar[i]=impar*impar;    
            impar+=2;
        }

        write(my_pipe[1],&Impar,sizeof(Impar)+1);
        exit(EXIT_SUCCESS);
        
    }else{
        if((pid2=fork())==0){
            
            close(my_pipe2[0]);
            printf("Child %d\n", getpid());
            int par=2;
            for(int i=0;i<10;i++){
                Par[i]=par*par;
                par+=2;
            } 
            write(my_pipe2[1],&Par,sizeof(Par)+1);
            
            
            exit(EXIT_SUCCESS);
            
        
        }else{
            printf("Father%d\n", getpid());

            waitpid(pid1,&status1,2);
            close(my_pipe[1]);

            waitpid(pid2,&status2,2);
            close(my_pipe2[1]);
            
           
            int ParS[10];
            int ImparS[10];
            int Total[20];

            
            
            read(my_pipe[0],ImparS,sizeof(ImparS));
            read(my_pipe2[0],ParS,sizeof(ParS));

            int indexImpar=0;
            int indexPar=0;

            

            for(int i = 0; i < 20;){
                Total[i]=ImparS[indexImpar];
                i++;
                indexImpar++;
                Total[i]=ParS[indexPar];
                i++;
                indexPar++;
            }

            for(int i=0;i<20;i++) printf("%i ", Total[i]);
            
        }
    }
    return 0;
}
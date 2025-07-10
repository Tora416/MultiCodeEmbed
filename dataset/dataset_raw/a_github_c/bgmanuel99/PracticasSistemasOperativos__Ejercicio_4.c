#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
int main(int argc, char const *argv[])
{
    pid_t pid, pid1, pid2, pid3;

    for(int i = 0; i < 4 ; i++){ 
        switch (pid = fork())
        {
        case 0:
            printf("PID hijo: %d, PID padre: %d\n",getpid(),getppid());
            if(i==0||i==1){
                for(int j = 0; j < 2; j++){ 
                    switch(pid1 = fork()){
                    case 0:
                        printf("PID hijo: %d, PID padre: %d\n",getpid(),getppid());
                        
                        if(j == 0){
                            switch(pid3 = fork()){
                            case 0:
                                printf("PID hijo: %d, PID padre: %d\n",getpid(),getppid());
                                break;
                            case -1:
                                printf("ERROR");
                                exit(-1);
                            default:
                                break;
                            }
                            if(pid3 == 0) break;
                        }
                        break;
                    case -1:
                        printf("ERROR");
                        exit(-1);
                    default:
                        break;
                    }
                    if(pid1 == 0) break;
                }
            }else if(i==2){
                
                switch(pid2 = fork())
                {
                case 0:
                    printf("PID hijo: %d, PID padre: %d\n",getpid(),getppid());
                    break;
                case -1:
                    printf("ERROR");
                    exit(-1);
                default:
                    break;
                }
                if(pid2 == 0) break;
            }
            break;
        case -1:
            printf("ERROR");
            exit(-1);
        default:
            break;
        }
        if(pid == 0) break;
    }

    

    return 0;
}
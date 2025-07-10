#include "fork.h"

int main()
{
    pid_t pid;

    pid = fork();

    if(pid == 0) {
        printf("child process....\n");
        printf("PID = %d\nPPID = %d\n",getpid(),getppid());
        printf("child process exit......\n");
    }
    else if(pid > 0 ){
        int status;
        printf("Before child process creation\n");

        pid_t wt_rv = wait(&status);
        printf("Parent process....\n");

        printf("PID = %d\nPPID = %d\n",getpid(),getppid());
        printf("Status %d\n",WIFEXITED(status));  

        printf("Wait ret value %d\n",wt_rv);
        printf("Parent process exit......\n");
    }
    else{
        printf("Fork failed\n");
    }
}

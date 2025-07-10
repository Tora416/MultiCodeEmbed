

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    pid_t pid = fork();
    if(pid == -1)
    {
        perror("fork error");
        exit(1);
    }
    else if(pid == 0)
    {
        printf("I'm child, pid = %d, going to sleep 10s\n", getpid());
        sleep(10);
        printf("--------child die---------\n");
    }
    else if(pid > 0)
    {
        int wpid;
        int status;
        
        wpid = wait(&status);       
        if(wpid == -1)
        {
            perror("wait error");
            exit(1);
        }
        if(WIFEXITED(status))       
        {
            printf("child exit with %d\n", WEXITSTATUS(status));
        }
        if(WIFSIGNALED(status))     
        {  
            printf("child bekill with signal %d\n", WTERMSIG(status));
        }
        printf("-----parent wait child %d finish-----\n", wpid);
    }

    return 0;
}
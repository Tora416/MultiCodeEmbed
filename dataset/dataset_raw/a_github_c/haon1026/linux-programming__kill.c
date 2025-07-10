

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>

int val = 100;

void sys_err(const char *str)
{
    perror(str);
    exit(1);
}

int main()
{
    pid_t pid = fork();
    if(pid > 0)
    {
        while(1)
        {
            printf("parent, pid = %d\n", getpid());
            sleep(1);
        }
    }
    else if(pid == 0)
    {
        

        

        sleep(5);
        printf("child pid = %d, ppid = %d\n", getpid(), getppid());         
        kill(0, SIGKILL);
    }
    
    return 0;
}
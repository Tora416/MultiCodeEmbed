

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

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
        printf("I'm child, my parent pid = %d, going to sleep 10s\n", getppid());
        sleep(10);
        printf("--------child die---------\n");
    }
    else if(pid > 0)
    {
        while(1)
        {
            printf("I'm parent, pid = %d, myson = %d\n", getpid(), pid);
            sleep(1);
        }
    }

    return 0;
}
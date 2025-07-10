

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
        while(1)
        {
            printf("I'm child, my parent pid = %d\n", getppid());
            sleep(1);
        }
    }
    else if(pid > 0)
    {
        printf("I'm parent, my pid = %d\n", getpid());
        sleep(9);
        printf("--------parent process going to die---------\n");
    }

    return 0;
}
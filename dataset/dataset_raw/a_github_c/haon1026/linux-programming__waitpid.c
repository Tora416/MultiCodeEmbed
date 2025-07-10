

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    int i;
    pid_t pid, wpid, temp;
    for(i = 0; i < 5; i++)
    {
        temp = fork();
        if(temp == 0)
            break;
        
        if(i == 2)
        {
            pid = temp;
            printf("2th child pid = %d\n", pid);
        }
    }

    if(i == 5)
    {
        sleep(5);
        
        wpid = waitpid(pid, NULL, WNOHANG);         
        if(wpid == -1)
        {
            perror("waitpid error");
            exit(1);
        }
        printf("I'm parent, wait a child finish : %d\n", wpid);
    }
    else
    {
        sleep(i);
        printf("I'm %dth child, pid = %d\n", i+1, getpid());
    }

    return 0;
}


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{
    pid_t pid;
    if((pid = fork()) < 0)
    {
        perror("fork error");
        exit(1);
    }
    else if(pid == 0)
    {
        sleep(5);
        printf("Child process PID is %d\n", getpid());
        printf("Group ID of child is %d\n", getpgid(0));
        printf("Session ID of child is %d\n", getsid(0));

        sleep(10);
        setsid();           

        printf("Changed:\n");

        printf("Child process PID is %d\n", getpid());
        printf("Group ID of child is %d\n", getpgid(0));
        printf("Session ID of child is %d\n", getsid(0));

        sleep(10);
    }

    sleep(5);       
    return 0;
}
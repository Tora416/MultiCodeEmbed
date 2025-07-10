

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char *argv[])
{
    printf("before fork-1-\n");
    printf("before fork-2-\n");
    printf("before fork-3-\n");
    printf("before fork-4-\n");

    pid_t pid = fork();
    if(pid == -1)
    {
        perror("fork error");
        exit(1);
    }
    else if(pid == 0)
    {
        printf("child is created\n");
    }
    else if(pid > 0)
    {
        printf("parent process:child is %d\n", pid);
    }

    printf("end of file\n");
    return 0;
}
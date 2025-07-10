

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

void sys_error(const char *str)
{
    perror(str);
    exit(1);
}

int main()
{
    int fd[2];
    int ret = pipe(fd);
    if(ret == -1)
        sys_error("pipe error");
    
    pid_t pid = fork();
    if(pid == -1)
    {   
        sys_error("fork error");
    }
    else if (pid > 0)
    {
        close(fd[1]);
        dup2(fd[0], STDIN_FILENO);
        execlp("wc", "wc", "-l", NULL);
        sys_error("execlp wc error");
    }
    else if (pid == 0)
    {
        close(fd[0]);
        dup2(fd[1], STDOUT_FILENO);
        execlp("ls", "ls", NULL);
        sys_error("execlp ls error");
    }

    return 0;
}
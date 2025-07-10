

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

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
    
    int i;
    for(i = 0; i < 2; i++)
    {
        pid_t pid = fork();
        if(pid == -1)
            sys_error("fork error");
        else if(pid == 0)
            break;
    }

    char buf[1024];
    if (i == 0)
    {
        close(fd[0]);
        write(fd[1], "1.hello\n", strlen("1.hello\n"));
    }
    else if (i == 1)
    {
        close(fd[0]);
        write(fd[1], "2.world\n", strlen("2.world\n"));
    }
    else if(i == 2)
    {
        close(fd[1]);
        
        int n = read(fd[0], buf, 1024);
        write(STDOUT_FILENO, buf, n);

        wait(NULL);
        wait(NULL);
    }

    return 0;
}
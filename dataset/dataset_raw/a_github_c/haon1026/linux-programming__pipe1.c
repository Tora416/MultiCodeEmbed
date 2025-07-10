

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void sys_error(char *str)
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
    
    char str[] = "hello world\n";
    char buf[100];
    int pid = fork();
    if(pid == 0)
    {
        close(fd[1]);
        
        int n = read(fd[0], buf, sizeof(buf));
        if(n > 0)
        {
            printf("%s", buf);
        }
        else
        {
            sys_error("read error");
        }
        close(fd[0]);
    }
    else if (pid > 0)
    {
        close(fd[0]);
        int n = write(fd[1], str, strlen(str));
        if(n > 0)
        {
            printf("write ok, n = %d\n", n);
        }
        sleep(1);
        close(fd[1]);
    }
    
    return 0;
}
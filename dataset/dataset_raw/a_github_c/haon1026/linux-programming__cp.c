

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
    int fd1 = open(argv[1], O_RDONLY);
    if(fd1 == -1)
    {
        perror("open argv1 error");
        exit(1);
    }

    int fd2 = open(argv[2], O_WRONLY|O_CREAT|O_TRUNC, 0644);
    if(fd2 == -1)
    {
        perror("open argv2 error");
        exit(1);
    }

    char buf[1024];
    int n = 0;
    while((n = read(fd1, buf, 1024)) != 0)
    {
        if(n < 0)
        {
            perror("read error");
            break;
        }
        write(fd2, buf, n);
    }

    close(fd1);
    close(fd2);
}   

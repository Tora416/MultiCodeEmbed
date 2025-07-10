

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define N 1

int main(int argc, char *argv[])
{
    int fd1 = open(argv[1], O_RDONLY);
    if(fd1 < 0)
    {
        perror("file1 open error");
        exit(1);
    }

    int fd2 = open(argv[2], O_WRONLY|O_CREAT|O_TRUNC, 0644);
    if(fd2 < 0)
    {
        perror("file2 open error");
        exit(1);
    }

    char buf[N];
    int n;
    while((n = read(fd1, buf, N)) != 0)
    {
        if(n < 0)
        {
            perror("read error");
            break;
        }
        write(fd2, buf, N);
    }

    close(fd1);
    close(fd2);
    return 0;
}





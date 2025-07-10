

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
    int fd1 = open(argv[1], O_RDWR|O_CREAT, 0644);   
    if(fd1 < 0)
    {
        perror("open error");
        exit(1);
    }

    int fd2 = open(argv[2], O_RDWR|O_CREAT, 0644);   
    if(fd2 < 0)
    {
        perror("open error");
        exit(1);
    }

    int newfd = dup2(fd1, fd2);                 
    printf("newfd = %d\n", newfd);

    int ret = write(fd2, "1234567", 7);         
    printf("ret = %d\n", ret);

    dup2(fd1, STDOUT_FILENO);                   
    printf("-------------------\n");

    close(fd1);
    close(newfd);
    return 0;
}
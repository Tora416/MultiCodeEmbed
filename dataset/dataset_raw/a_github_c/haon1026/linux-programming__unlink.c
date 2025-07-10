

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

int main()
{
    int fd = open("temp.txt", O_RDWR|O_CREAT|O_TRUNC, 0644);
    if(fd < 0)
    {
        perror("open temp error");
        exit(1);
    }

    int ret;
    ret = unlink("temp.txt");       
    if(ret < 0)
    {
        perror("unlink error");
        exit(1);
    }

    char *p1 = "test of unlink\n";
    char *p2 = "after write something\n";
    ret = write(fd, p1, strlen(p1));
    if(ret == -1)
        perror("write error");

    printf("write ok\n");
    ret = write(fd, p2, strlen(p2));
    if(ret == -1)
        perror("write error");

    printf("Enter any key continue\n");
    getchar();

    

    close(fd);

    

    return 0;
}
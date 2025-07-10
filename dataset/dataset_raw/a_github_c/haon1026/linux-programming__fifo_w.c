

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>

void sys_error(const char *str)
{
    perror(str);
    exit(1);
}

int main(int argc, char *argv[])
{
    if(argc < 2)
    {
        printf("enter a fifo name\n");
        return -1;
    }

    int fd = open(argv[1], O_WRONLY);
    if(fd < 0)
        sys_error("open error");
    
    int i = 0;
    char buf[1024];
    while(1)
    {
        sprintf(buf, "hello world %d\n", i++);
        write(fd, buf, strlen(buf));
        sleep(1);
    }

    close(fd);
    return 0;
}

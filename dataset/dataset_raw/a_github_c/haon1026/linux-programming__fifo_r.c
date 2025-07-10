

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

    int fd = open(argv[1], O_RDONLY);
    if(fd < 0)
        sys_error("open error");
    
    int n;
    char buf[1024];
    while(1)
    {
        n = read(fd, buf, sizeof(buf));
        write(STDOUT_FILENO, buf, n);
        sleep(1);
    }

    close(fd);
    return 0;
}

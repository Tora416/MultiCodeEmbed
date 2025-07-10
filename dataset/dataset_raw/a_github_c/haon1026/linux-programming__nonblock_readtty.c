

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

int main()
{
    int fd = open("/dev/tty", O_RDONLY|O_NONBLOCK);
    if(fd < 0)
    {
        perror("open /dev/tty");
        exit(1);
    }
    printf("open /dev/tty ok, fd = %d\n", fd);

    char buf[10];
    int n;
    while(1)
    {
        n = read(fd, buf, 10);
        if(n < 0)
        {
            if(errno != EAGAIN)
            {
                perror("read /dev/tty");
                exit(1);
            }
            else
            {
                write(STDOUT_FILENO, "try again\n", strlen("try again\n"));
                sleep(2);
                continue;
            }
        }
        break;
    }

    write(STDOUT_FILENO, buf, n);
    close(fd);

    return 0;
}

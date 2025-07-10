

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

#define MSG_TRY "try again\n"

int main()
{
    int flags = fcntl(STDIN_FILENO, F_GETFL);   
    if(flags == -1)
    {
        perror("fcntl error");
        exit(1);
    }
    
    flags |= O_NONBLOCK;
    int ret = fcntl(STDIN_FILENO, F_SETFL, flags);
    if(ret == -1)
    {
        perror("fcntl error");
        exit(1);
    }

    char buf[10];
    int n;
    while(1)
    {
        n = read(STDIN_FILENO, buf, 10);
        if(n < 0)
        {
            if(errno != EAGAIN)
            {
                perror("read /dev/tty");
                exit(1);
            }
            else
            {
                write(STDOUT_FILENO, MSG_TRY, strlen(MSG_TRY));
                sleep(2);
                continue;
            }
        }
        break;
    }

    write(STDOUT_FILENO, buf, n);

    return 0;
}




#include <stdio.h>
#include <stdlib.h>
#include <sys/epoll.h>
#include <errno.h>
#include <unistd.h>

#define MAXLINE 10

int main(int argc, char *argv[])
{
    char buf[MAXLINE];
    char ch = 'a';

    int pfd[2];
    pipe(pfd);

    pid_t pid = fork();
    if(pid == 0)            
    {
        close(pfd[0]);
        int i;
        while(1)
        {
            
            for(i = 0; i < MAXLINE/2; i++)
            {
                buf[i] = ch;
            }
            buf[i-1] = '\n';
            ch++;

            
            for(; i < MAXLINE; i++)
            {
                buf[i] = ch;
            }
            buf[i-1] = '\n';
            ch++;
            
            write(pfd[1], buf, sizeof(buf));
            sleep(5);
        }
        close(pfd[1]);
    }
    else if(pid > 0)        
    {
        close(pfd[1]);

        struct epoll_event event;               
        struct epoll_event resevent[10];        
 
        int efd = epoll_create(10);
        event.events = EPOLLIN|EPOLLET;         
        
        event.data.fd = pfd[0];
        epoll_ctl(efd, EPOLL_CTL_ADD, pfd[0], &event);

        int res, len;
        while(1)
        {
            res = epoll_wait(efd, resevent, 10, -1);
            
            if(resevent[0].data.fd == pfd[0])
            {
                len = read(pfd[0], buf, MAXLINE/2);
                write(STDOUT_FILENO, buf, len);
            }
        }

        close(pfd[0]);
        close(efd);
    }
    else
    {
        perror("fork");
        exit(-1);
    }
    return 0;
}

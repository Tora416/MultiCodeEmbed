


#include "../../base.h"
#include <strings.h>
#include <sys/epoll.h>
#include <fcntl.h>          

#define MAXLINE 10

int main(int argc, char *argv[])
{
    int serv_sock = Socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in serv_adr;
    bzero(&serv_adr, sizeof(serv_adr));
    serv_adr.sin_family = AF_INET;
    serv_adr.sin_port = htons(9999);
    serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);

    Bind(serv_sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr));

    Listen(serv_sock, 128);

    struct epoll_event event;               
    struct epoll_event resevent[10];        

    int efd = epoll_create(10);
    event.events = EPOLLIN|EPOLLET;       

    printf("Accepting connection ...\n");

    struct sockaddr_in clnt_adr;
    socklen_t clnt_adr_len = sizeof(clnt_adr);
    int clnt_sock = Accept(serv_sock, (struct sockaddr*)&clnt_adr, &clnt_adr_len);

    char str[INET_ADDRSTRLEN];
    printf("receive from %s at PORT %d\n", inet_ntop(AF_INET, &clnt_adr.sin_addr, str, sizeof(str)), ntohs(clnt_adr.sin_port));

    int flag = fcntl(clnt_sock, F_GETFL);       
    flag |= O_NONBLOCK;
    fcntl(clnt_sock, F_SETFL, flag);

    event.data.fd = clnt_sock;
    epoll_ctl(efd, EPOLL_CTL_ADD, clnt_sock, &event);

    int res, len;
    char buf[MAXLINE];
    while(1)
    {
        printf("epoll_wait begin\n");
        res = epoll_wait(efd, resevent, 10, -1);
        printf("epoll_wait end res %d\n", res);

        if(resevent[0].data.fd == clnt_sock)
        {
            while((len = read(clnt_sock, buf, MAXLINE/2)) > 0)      
                write(STDOUT_FILENO, buf, len);
        }
    }

    Close(serv_sock);
    Close(efd);
    return 0;
}

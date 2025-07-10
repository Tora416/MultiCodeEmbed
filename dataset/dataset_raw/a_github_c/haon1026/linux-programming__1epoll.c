


#include "../../base.h"
#include <ctype.h>
#include <strings.h>
#include <sys/epoll.h>

#define MAXLINE 80
#define OPEN_MAX 1024

int main()
{
    int serv_sock = Socket(AF_INET, SOCK_STREAM, 0);

    int opt = 1;
    setsockopt(serv_sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    struct sockaddr_in serv_adr;
    bzero(&serv_adr, sizeof(serv_adr));
    serv_adr.sin_family = AF_INET;
    serv_adr.sin_port = htons(9999);
    serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);

    Bind(serv_sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr));

    Listen(serv_sock, 128);

    int epfd = epoll_create(OPEN_MAX);                          
    if(epfd == -1)
        sys_err("epoll_create() error");

    struct epoll_event temp;                                    
    struct epoll_event ep[OPEN_MAX];                            

    temp.events = EPOLLIN;                                      
    temp.data.fd = serv_sock;

    int res = epoll_ctl(epfd, EPOLL_CTL_ADD, serv_sock, &temp); 
    if(res == -1)
        sys_err("epoll_ctl() error");

    
    char buf[MAXLINE], str[INET_ADDRSTRLEN];
    struct sockaddr_in clnt_adr;
    socklen_t clnt_adr_len;
    int ret, conn_sock, clnt_sock, i, n, num = 0;
    while(1)
    {
        ret = epoll_wait(epfd, ep, OPEN_MAX, -1);               
        if(ret == -1)
            sys_err("epoll_wait() error");
        
        for(i = 0; i < ret; i++)
        {
            if(!ep[i].events & EPOLLIN)                         
                continue;
            
            if(ep[i].data.fd == serv_sock)
            {
                clnt_adr_len = sizeof(clnt_adr);
                conn_sock = Accept(serv_sock, (struct sockaddr*)&clnt_adr, &clnt_adr_len);

                printf("receive from %s at PORT %d\n", inet_ntop(AF_INET, &clnt_adr.sin_addr, str, sizeof(str)), ntohs(clnt_adr.sin_port));
                printf("cfd %d --- client %d\n", conn_sock, ++num);

                temp.events = EPOLLIN;
                temp.data.fd = conn_sock;
                res = epoll_ctl(epfd, EPOLL_CTL_ADD, conn_sock, &temp);     
                if(res == -1)
                    sys_err("epoll_ctl() error");
            }
            else
            {
                clnt_sock = ep[i].data.fd;
                n = Read(clnt_sock, buf, MAXLINE);
                if(n == 0)
                {
                    res = epoll_ctl(epfd, EPOLL_CTL_DEL, clnt_sock, NULL);  
                    if(res == -1)
                        sys_err("epoll_ctl() error");
                    Close(clnt_sock);
                    printf("client[%d] closed connection\n", clnt_sock);
                }
                else
                {
                    for(i = 0; i < n; i++)
                        buf[i] = toupper(buf[i]);
                    
                    Write(STDOUT_FILENO, buf, n);
                    Write(clnt_sock, buf, n);
                }
            }
        }
    }
    Close(serv_sock);
    Close(epfd);
    return 0;
}
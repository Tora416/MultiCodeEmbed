


#include "../../base.h"
#include <ctype.h>
#include <strings.h>
#include <poll.h>

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

    struct pollfd client[OPEN_MAX];
    client[0].fd = serv_sock;       
    client[0].events = POLLIN;      

    for(int i = 1; i < OPEN_MAX; i++)
    {
        client[i].fd = -1;
    }

    int maxi = 0;           
    char buf[MAXLINE], str[INET_ADDRSTRLEN];
    struct sockaddr_in clnt_adr;
    socklen_t clnt_adr_len;
    int ret, conn_sock, clnt_sock, i, n;
    while(1)
    {
        ret = poll(client, maxi+1, -1);
        if(ret < 0)
        {
            sys_err("poll() err");
        }

        if(client[0].revents & POLLIN)
        {
            clnt_adr_len = sizeof(clnt_adr);
            conn_sock = Accept(serv_sock, (struct sockaddr*)&clnt_adr, &clnt_adr_len);
            printf("receive from %s at PORT %d\n", inet_ntop(AF_INET, &clnt_adr.sin_addr, str, sizeof(str)), ntohs(clnt_adr.sin_port));

            for(i = 1; i < OPEN_MAX; i++)
            {
                if(client[i].fd < 0)
                {
                    client[i].fd = conn_sock;           
                    break;
                }
            }
            if(i == OPEN_MAX)
            {
                fputs("too many clients\n", stderr);            
                exit(1);
            }
            
            client[i].events = POLLIN;                  
            if(i > maxi)
                maxi = i;                               
            if(--ret <= 0)
                continue;                               
        }

        for(i = 1; i <= maxi; i++)
        {
            if((clnt_sock = client[i].fd) < 0)
                continue;

            if(client[i].revents & POLLIN)
            {
                if((n = Read(clnt_sock, buf, MAXLINE)) < 0)
                {
                    if(errno == ECONNRESET)             
                    {
                        printf("client[%d] aborted connection\n", i);
                        Close(clnt_sock);
                        client[i].fd = -1;              
                    }
                    else
                    {
                        sys_err("read() error");
                    }
                }
                else if(n == 0)                         
                {
                    printf("client[%d] closed connection\n", i);
                    Close(clnt_sock);
                    client[i].fd = -1;
                }
                else
                {
                    for(int j = 0; j < n; j++)
                        buf[j] = toupper(buf[j]);
                    Write(clnt_sock, buf, n);
                }

                if(--ret <= 0)
                    break;
            }
        }
    }
    Close(serv_sock);
    return 0;
}



#include "../../base.h"
#include <strings.h>
#include <ctype.h>
#include <sys/select.h>

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

    Bind(serv_sock, (struct sockaddr *)&serv_adr, sizeof(serv_adr));

    Listen(serv_sock, 128);

    int maxfd = serv_sock;          

    fd_set rset, allset;            
    FD_ZERO(&allset);               
    FD_SET(serv_sock, &allset);     
     
    int clnt_sock;
    struct sockaddr_in clnt_adr;
    socklen_t clnt_adr_len;
    char buf[BUFSIZ];
    int ret, n;
    while(1)
    {
        rset = allset;              
        ret = select(maxfd+1, &rset, NULL, NULL, NULL);     
        if (ret < 0)
        {
            sys_err("select() error");
        }

        if(FD_ISSET(serv_sock, &rset))                      
        {
            clnt_adr_len = sizeof(clnt_adr);
            clnt_sock = Accept(serv_sock, (struct sockaddr*)&clnt_adr, &clnt_adr_len);      
            FD_SET(clnt_sock, &allset);                     
            
            if(maxfd < clnt_sock)       
                maxfd = clnt_sock;
            
            if(ret == 1)                
                continue;
        }

        for(int i = serv_sock+1; i <= maxfd; i++)   
        {
            if(FD_ISSET(i, &rset))
            {
                n = Read(i, buf, sizeof(buf));
                if(n == 0)
                {
                    Close(i);
                    FD_CLR(i, &allset);             
                }
                else
                {
                    for(int j = 0; j < n; j++)
                    {
                        buf[j] = toupper(buf[j]);
                    }
                    Write(i, buf, n);
                    Write(STDOUT_FILENO, buf, n);
                }
            }
        } 
    }

    Close(serv_sock);
    return 0;
}
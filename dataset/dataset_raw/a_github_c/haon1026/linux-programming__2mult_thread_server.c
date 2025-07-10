


#include "../base.h"
#include <strings.h>    
#include <ctype.h>
#include <pthread.h>

struct clnt_info                
{
    struct sockaddr_in clnt_addr;
    int clnt_sock; 
};

void *do_work(void *arg)
{
    struct clnt_info *p_cInfo = (struct clnt_info *)arg;
    char buf[BUFSIZ];
    char str[16];       
    int n;

    while(1)
    {
        n = Read(p_cInfo->clnt_sock, buf, sizeof(buf));
        if(n == 0)
        {
            printf("the client %d closed...\n", p_cInfo->clnt_sock);
            break;
        }

        printf("received from %s at PORT %d\n", inet_ntop(AF_INET, &(p_cInfo->clnt_addr.sin_addr), str, sizeof(str)), ntohs(p_cInfo->clnt_addr.sin_port));  

        for(int i = 0; i < n; i++)
        {
            buf[i] = toupper(buf[i]);
        }

        Write(STDOUT_FILENO, buf, n);
        Write(p_cInfo->clnt_sock, buf, n);
    }
    Close(p_cInfo->clnt_sock);
    return (void*)0;        
}

int main()
{
    int serv_sock = Socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in serv_addr;
    bzero(&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(9999);
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    
    
    Bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));

    Listen(serv_sock, 128);

    printf("Accepting client connect...\n");
    struct clnt_info c_info[256];
    int i = 0;
    int clnt_sock;
    struct sockaddr_in clnt_addr;
    socklen_t clnt_addr_len;
    pthread_t tid;
    while(1)
    {
        clnt_addr_len = sizeof(clnt_addr);
        clnt_sock = Accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_addr_len);
        c_info[i].clnt_addr = clnt_addr;
        c_info[i].clnt_sock = clnt_sock;

        pthread_create(&tid, NULL, do_work, (void*)&c_info[i]);     
        pthread_detach(tid);            
        i++;
    }

    return 0;
}
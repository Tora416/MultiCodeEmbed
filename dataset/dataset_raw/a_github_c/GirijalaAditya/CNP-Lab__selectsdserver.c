#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<sys/select.h>
#include<sys/time.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<netinet/ip.h>
#include<string.h>
#define STDIN 1
void main(int argc,char* argv[])
{
    
    int rval,sockid;
    
    sockid=socket(AF_INET,SOCK_STREAM,6);   
    if(sockid==-1)
    {
        perror("SOCK-CRE-ERR:");
        exit(1);
    }
    struct sockaddr_in s,c;
    
    system("clear");
    if(argc<2)
    {
        printf("\nUSAGE : %s IP_ADDR PORT#\n",argv[0]);
        exit(1);
    }
    s.sin_family=AF_INET;
    s.sin_port=htons(atoi(argv[2]));
    s.sin_addr.s_addr=inet_addr(argv[1]);
    
    rval=bind(sockid,(struct sockaddr*)&s,sizeof(s)); 
    if(rval==-1)  
    {   
        perror("BIND-ERR:");   
        close(sockid);   
        exit(1);  
    }   
    rval=listen(sockid,5);
    if(rval==-1)  
    {   
        perror("LISTEN-ERR:");   
        close(sockid);   
        exit(1);  
    }  
    fd_set rdfs,copy;
    FD_ZERO(&rdfs);
    FD_SET(STDIN,&rdfs);
    FD_SET(sockid,&rdfs);
    int maxfd=STDIN>=sockid?STDIN:sockid;
    maxfd=maxfd+1;
    char msg[100];
    struct timeval tm;
    int ret;


    while(1)
    {
        copy=rdfs;
        tm.tv_sec=5;
        tm.tv_usec=5000000;
        ret=select(maxfd,&copy,NULL,NULL,&tm);
        if(ret==-1)
        perror("SEL-ERR");
        if(ret==0)
        printf("Timeout occured");
        else
        {
            if(FD_ISSET(STDIN,&copy))
            {
                scanf("%s",msg);
                printf("Message is:%s\n",msg);
            }
            if(FD_ISSET(sockid,&copy))
            {
                int clen=sizeof(c);  
                int sid1=accept(sockid,(struct sockaddr*)&c,&clen); 
                if(sid1==-1)
                {
                    perror("ACC-ERR");
                    exit(0);
                }
                FD_SET(sid1,&rdfs);
                maxfd=maxfd>=sid1?maxfd:sid1;
                maxfd=maxfd+1;
                int k=recv(sid1,msg,sizeof(msg),0);
                msg[k]='\0';
                printf("Message from client is:%s\n",msg);
                close(sid1);
                FD_CLR(sid1,&rdfs);
            }
        }
     
    }
    close(sockid);          
}




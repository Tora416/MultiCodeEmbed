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
    char msg[30];
    rval=connect(sockid,(struct sockaddr*)&s, sizeof(s)); 
    if(rval==-1)  
    {   
        perror("CONN-ERR:");   
        close(sockid);   
        exit(1);
    }
    printf("\nEnter the request message : ");  
    scanf("%s",msg);  
    send(sockid,msg,sizeof(msg),0); 
    close(sockid);
}

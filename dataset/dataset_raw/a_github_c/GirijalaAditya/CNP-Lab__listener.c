#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<string.h>
void main(int argc,char* argv[])
{
    int sockid,rval,count=0,tlen;
    char msg[100];
    struct sockaddr_in lis,talk;
    system("clear");
    if(argc<3)
    {
        printf("\nUSAGE : %s IP_ADDR PORT#\n",argv[0]);
        exit(1);
    }
    lis.sin_family=AF_INET;
    lis.sin_port=htons(atoi(argv[2]));
    lis.sin_addr.s_addr=inet_addr(argv[1]);
    sockid=socket(AF_INET,SOCK_DGRAM,0);
    if(sockid==-1)
    {
        perror("SOCK-CRE-ERR:");
        exit(1);
    }
    rval=bind(sockid,(struct sockaddr*)&lis,sizeof(lis));
    if(rval==-1)
    {
        perror("BIND-ERR:");
        close(sockid);
        exit(1);
    }
    printf("\nThe Listener is ready to accept messages\n");
    tlen=sizeof(talk);
    while(1)
    {
        strncpy(msg," ",100);
        rval=recvfrom(sockid,msg,sizeof(msg),0,(struct sockaddr*)&talk,&tlen);
        if(rval==-1)
        {
            perror("MSG-RCV-ERR:");
            close(sockid);
            exit(1);
        }
        printf("\nMessage %d read is %s\n",++count,msg);
        if(!strcmp(msg,"EXIT"))
        break;
    }
    close(sockid);
}

#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
void main(int argc,char* argv[])
{
    int sockid,rval;
    char m1[20],m2[20];
    sockid=socket(AF_INET,SOCK_STREAM,0);
    if(sockid==-1)
    {
        perror("SOCK-CRE-ERR");
        exit(1);
    }
    struct sockaddr_in s;
    system("clear");
    if(argc<3)
    {
        printf("\nUSAGE : %s IP_ADDR PORT#\n",argv[0]);
        exit(0);
    }
    s.sin_family=AF_INET;
    s.sin_port=htons(atoi(argv[2]));
    s.sin_addr.s_addr=inet_addr(argv[1]);
    rval=connect(sockid,(struct sockaddr*)&s, sizeof(s));
    if(rval==-1)
    {
        perror("CONN-ERR:");
        close(sockid);
        exit(1);
    }
    printf("\nEnter the request message : ");
    scanf("%s",m1);
    rval=send(sockid,m1,sizeof(m1),0);
    if(rval==-1)
    {
        perror("MSG-SND-ERR:");
        close(sockid);
        exit(1);
    }
    printf("\nMessage sent successfully\n");
    rval=recv(sockid,m2,sizeof(m2),0);
    if(rval==-1)
    {
        perror("MSG-RCV-ERR:");
        close(sockid);
        exit(1);
    }
    printf("\nServer response is : %s\n",m2);
    close(sockid);
}

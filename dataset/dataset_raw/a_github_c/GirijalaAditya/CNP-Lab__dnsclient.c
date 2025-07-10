#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string.h>
void main(int argc,char* argv[])
{
    struct sockaddr_in dnss;
    int sockid,rval;
    char sym[20],IP[20];
    int slen;
    system("clear");
    if(argc<3)
    {
        printf("\nUSAGE : %s IP_ADDR PORT#\n",argv[0]);
        exit(1);
    }
    sockid=socket(AF_INET,SOCK_DGRAM,0);
    if(sockid==-1)
    {
        perror("SOCK-CRE-ERR:");
        exit(1);
    }
    dnss.sin_family=AF_INET;
    dnss.sin_port=htons(atoi(argv[2]));
    dnss.sin_addr.s_addr=inet_addr(argv[1]);
    printf("\nEnter the symbolic name of resource : ");
    scanf("%s",sym);
    rval=sendto(sockid,sym,sizeof(sym),0,(struct sockaddr*)&dnss,sizeof(dnss));
    if(rval==-1)
    {
        perror("MSG-SND-ERR:");
        close(sockid);
        exit(1);
    }
    printf("\nWaiting to receive from DNS Server\n");
    slen=sizeof(dnss);
    strncpy(IP," ",20);
    rval=recvfrom(sockid,IP,sizeof(IP),0,(struct sockaddr*)&dnss,&slen);
    if(rval==-1)
    {
        perror("MSG-RCV-ERR:");
        close(sockid);
        exit(1);
    }
    printf("\nEquivalent IP adrress of %s is %s\n",sym,IP);
    close(sockid);
}

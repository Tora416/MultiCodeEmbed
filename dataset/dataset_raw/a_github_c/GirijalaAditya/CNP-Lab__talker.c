#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<string.h>
void main(int argc,char* argv[])
{
    int rval,sockid,itr,i;
    char msg[100];
    struct sockaddr_in lis;
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
    printf("\nEnter the number of messages to be sent: ");
    scanf("%d",&itr);
    for(i=1;i<=itr;i++)
    {
        strncpy(msg," ",100);
        printf("Enter the message %d : ",i);
        scanf("%s",msg);
        rval=sendto(sockid,msg,sizeof(msg),0,(struct sockaddr*)&lis,sizeof(lis));
        if(rval<=0)
        {
            perror("MSG-SND-ERR:");
            close(sockid);
            exit(1);
        }
        printf("\nMessage sent successfully\n");
        if(strcmp(msg,"EXIT")==0)
        {
            close(sockid);
            exit(1);
        }
    }
    close(sockid);
}

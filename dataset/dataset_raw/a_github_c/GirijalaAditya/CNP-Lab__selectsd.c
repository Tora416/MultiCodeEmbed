#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<sys/select.h>
#include<sys/time.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<string.h>
void main(int argc,char* argv[])
{
    fd_set rdfs;
    int rval,sockid;
    char buf1[3],buf2[30];
    sockid=socket(AF_INET,SOCK_STREAM,6);   
    if(sockid==-1)
    {
        perror("SOCK-CRE-ERR:");
        exit(1);
    }
    struct sockaddr_in s;
    struct timeval tv;
    system("clear");
    if(argc<2)
    {
        printf("\nUSAGE : %s IP_ADDR PORT#\n",argv[0]);
        exit(1);
    }
    s.sin_family=AF_INET;
    s.sin_port=htons(atoi(argv[2]));
    s.sin_addr.s_addr=inet_addr(argv[1]);
    
    
    rval=connect(sockid,(struct sockaddr *)&s,sizeof(s));
    if(rval==-1)    
    {
        perror("CONNECT_ERR");
        close(sockid);
        exit(1);
    }
    printf("\n Enter the data to send:\t");
    scanf("%s",buf1);
    send(sockid,(char *) buf1,sizeof(buf1),0);
    do
    {
        FD_ZERO(&rdfs);
        FD_SET(sockid,&rdfs);
        rval=select(sockid+1,&rdfs,NULL,NULL,NULL);
        printf("\nrval of select = %d\n",rval);
    }while(rval==-1);
    if(rval>0)
    {
        if(FD_ISSET(sockid,&rdfs))
        {
            rval=recv(sockid,(char *)buf2,sizeof(buf2),0);
            if(rval==0)
            printf("\nNo response from server\n");
            else
            printf("\nServer Response is %s\n",buf2);
        }
    }
    else
    perror("SELECT_ERR");
    close(sockid);
}

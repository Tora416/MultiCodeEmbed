#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<sys/uio.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<string.h>
void main(int argc,char* argv[])
{
    int sockid,rval;
    char a1[50],a2[50],b1[50],b2[50];
    sockid=socket(AF_INET,SOCK_STREAM,0);
    if(sockid==-1)
    {
        perror("SOCK-CRE-ERR");
        exit(1);
    }
    struct sockaddr_in s;
    struct iovec iov[2]; 
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
    printf("\nEnter the first message : ");
    scanf("%s",a1);
    printf("\nEnter the second message : ");
    scanf("%s",a2);
    iov[0].iov_base=a1;  
    iov[0].iov_len=50;  
    iov[1].iov_base=a2;  
    iov[1].iov_len=50;  
    writev(sockid,&iov[0],2); 
    printf("Message sent successfully\n");
    iov[0].iov_base=b1;  
    iov[0].iov_len=50;  
    iov[1].iov_base=b2;  
    iov[1].iov_len=50;  
    readv(sockid,&iov[0],2);  
    printf("Server response is :  %s \n %s\n",b1,b2); 

    close(sockid);
}

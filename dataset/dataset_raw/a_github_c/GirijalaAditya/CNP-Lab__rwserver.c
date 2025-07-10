#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<sys/uio.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
void main(int argc,char*argv[])
{
    int sid,sid1,rval;
    struct sockaddr_in s,c;
    struct iovec iov[2];
    char b1[50],b2[50]; 
    int clen; 
    system("clear");
    if(argc<3)
    {
        printf("\nUSAGE : %s IP_ADDRESS PORT#\n",argv[0]);
        exit(0);
    }
    sid=socket(AF_INET,SOCK_STREAM,6);
    if(sid==-1)
    {
        perror("SOCK-CRE-ERR:");
        exit(1);
    }
    s.sin_family=AF_INET;
    s.sin_port=htons(atoi(argv[2]));
    s.sin_addr.s_addr=inet_addr(argv[1]);
    rval=bind(sid,(struct sockaddr*)&s,sizeof(s));
    if(rval==-1)    
    {
        perror("BIND-ERR:");
        close(sid);
        exit(1);
    }
    rval=listen(sid,5);
    if(rval==-1)
    {
        perror("LISTEN-ERR:");
        close(sid);
        exit(1);
    }
    clen=sizeof(c);
    sid1=accept(sid,(struct sockaddr*)&c,&clen);
    if(sid1<0)
    {
        printf("Connection Failed");
    }
    iov[0].iov_base=b1;  
    iov[0].iov_len=50;  
    iov[1].iov_base=b2; 
    iov[1].iov_len=50;  
    readv(sid1,&iov[0],2);  
    printf("Client Message is %s \n %s\n",b1,b2);  
    writev(sid1,&iov[0],2); 
    printf("Response Sent\n");
    close(sid);
    close(sid1);
}

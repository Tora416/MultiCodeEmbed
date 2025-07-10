#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<time.h>
#include<string.h>
void main(int argc,char*argv[])
{
    int sid,sid1,rval;
    time_t t=time(0);
    struct sockaddr_in s,c;
    char buffer[20],smsg[30];
    strcpy(smsg,ctime(&t));
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
    rval=recv(sid1,buffer,sizeof(buffer),0);
    if(rval==-1)
    {
        perror("MSG-RCV-ERR:");
    }
    else
    {
        printf("\nClient request is %s\n",buffer);
    }
    strcpy(smsg,ctime(&t));
    rval=send(sid1,smsg,sizeof(smsg),0);
    if(rval==-1)
    {
        perror("MSG-SND-ERR:");
    }
    else
    {
        printf("\nResponse sent\n");
    }
    close(sid);
    close(sid1);
}

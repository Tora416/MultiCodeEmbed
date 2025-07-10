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
    struct sockaddr_in dnss,dnsc;
    int rval,sockid,flag=0,clen;
    char sym[20],IP[20],dnsFile[20],dnsName[20];
    FILE *fptr;
    system("clear");
    if(argc<3)
    {
        printf("\nUSAGE : %s IP_ADDR PORT#\n",argv[0]);
        exit(1);
    }
    dnss.sin_family=AF_INET;
    dnss.sin_port=htons(atoi(argv[2]));
    dnss.sin_addr.s_addr=inet_addr(argv[1]);
    sockid=socket(AF_INET,SOCK_DGRAM,0);
    if(sockid==-1)
    {
        perror("SOCK-CRE-ERR:");
        exit(1);
    }
    rval=bind(sockid,(struct sockaddr*)&dnss,sizeof(dnss));
    if(rval==-1)
    {
        perror("BIND-ERR:");
        close(sockid);
        exit(1);
    }
    printf("\nDNS Server waiting for request\n");
    printf("\nEnter the DNS file name : ");
    scanf("%s",dnsFile);
    
    fptr=fopen(dnsFile,"r");
    if(fptr==NULL)
    {
        perror("FILE-OPEN-ERR:");
        close(sockid);
        exit(1);
    }
    clen=sizeof(dnsc);
    rval=recvfrom(sockid,sym,sizeof(sym),0,(struct sockaddr*)&dnsc,&clen);
    if(rval==-1)
    {
        perror("MSG-RCV-ERR:");
        close(sockid);
        fclose(fptr);
        exit(1);
    }
    printf("\nIP requested for %s\n",sym);
    while((fscanf(fptr,"%s%s",dnsName,IP) != EOF) )
    {
        if(strcmp(dnsName,sym)==0)
        {
            rval=sendto(sockid,IP,sizeof(IP),0,(struct
            sockaddr*)&dnsc,clen);
            if(rval==-1)
            {
                perror("MSG-SND-ERR:");
                fclose(fptr);
                close(sockid);
                exit(1);
            }
            flag=1;
        }
        printf("\n flag value in loop is %d\n",flag);
        if(flag==1) 
        break;
    }
    if(flag==0)
    {
        printf("\n invalid domain name case\n");
        rval=sendto(sockid,"NOT FOUND",sizeof("NOT FOUND"),0,(struct
        sockaddr*)&dnsc,clen);
        if(rval==-1)
        {
            perror("MSG-SND-ERR:");
            fclose(fptr);
            close(sockid);
            exit(1);
        }
    }
    fclose(fptr);
    close(sockid);
}

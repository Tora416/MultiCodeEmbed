#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>
typedef struct msg
{
    long id;
    char txt[10];
}message;
void main()
{
    int mqid,rval,msgid;
    message m1;
    mqid=msgget((key_t)80,IPC_CREAT|0666);
    if(mqid==-1)
    {
        perror("MQ-CRE-ERR");
        exit(1);
    }
    system("ipcs -q");
    printf("Enter the msgid : ");
    scanf("%d",&msgid);
    m1.id=msgid;
    printf("Enter the message : ");
    scanf("%s",m1.txt);
    rval=msgsnd(mqid,(message*)&m1,sizeof(m1),0);
    if(rval==-1)
    perror("\nMessage not sent\n");
    else
    printf("\nMessage Sent successfully\n");
}

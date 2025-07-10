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
    message m2;
    mqid=msgget((key_t)80,IPC_CREAT|0666);
    if(mqid==-1)
    {
        perror("MQ-CRE-ERR");
        exit(1);
    }
    system("ipcs -q");
    printf("\nEnter the msgid :");
    scanf("%d",&msgid);
    rval=msgrcv(mqid,(message*)&m2,sizeof(m2),msgid,0);
    if(rval==-1)
    {
        perror("No message read");
        msgctl(mqid,IPC_RMID,0);
        system("ipcs -q");
        exit(1);
    }
    printf("\nMessage entered : %s\n",m2.txt);
    msgctl(mqid,IPC_RMID,0);
    system("ipcs -q");
}

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
    int mqid,pid,rval,msgid;
    system("clear");
    printf("\nBasic operations on message queues\n");
    printf("\nPP : process id is %d\n",getpid());
    mqid=msgget((key_t)80,IPC_CREAT|0666);
    if(mqid==-1)
    {
        perror("PP : MQ-CRE-ERR");
        exit(1);
    }
    system("ipcs -q");
    pid=fork();
    if(pid==-1)
    {
        perror("PP : FRK-ERR");
        msgctl(mqid,IPC_RMID,0);
        system("ipcs -q");
        exit(1);
    }   
    if(pid==0)
    {
        message m1;
        printf("\nCP : In child process\tpid=%d\n",getpid());
        printf("\nCP : Parent process id\tppid=%d\n",getppid());
        printf("\nEnter the message : ");
        scanf("%s",m1.txt);
        rval=msgsnd(mqid,(message*)&m1,sizeof(m1),0);
        if(rval==-1)
        perror("\nCP : Unable to send message\n");
        else
        printf("\nCP : message successfully sent\n");
    }
    else
    {
        message m2;
        rval=msgrcv(mqid,(message*)&m2,sizeof(m2),msgid,0);
        if(rval==-1)
        perror("\nPP : No message read\n");
        else
        printf("\n PP : Client message read from queue is %s\n",m2.txt);
        rval=msgctl(mqid,IPC_RMID,0);
        system("ipcs -q");
    }
}

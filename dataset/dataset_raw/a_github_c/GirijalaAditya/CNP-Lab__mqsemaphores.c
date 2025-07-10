#include<stdio.h>
#include<sys/types.h>
#include<semaphore.h>
#include<unistd.h>
#include<stdlib.h>
#include<pthread.h>
#include<sys/shm.h>
#include<sys/ipc.h>
#include<sys/msg.h>
typedef struct msg
{
    long id;
    char txt[10];
}message;
void main(int argc, char* argv[])
{

    int label, mem_size;
    int shmid,sval,inval,rval,mqid,pid;
    int msgid; 
    sem_t *s;
    system("clear");
    if(argc<3)
    {
        printf("\nUSAGE : %s LabelForResources MemorySize(inbytes)\n",argv[0]);
        exit(1);
    }
    label=atoi(argv[1]);
    mqid=msgget((key_t)label,IPC_CREAT|0666);
    if(mqid==-1)
    {
        perror("MSG-Q-CRE-ERR:");
        exit(1);
    }
    system("ipcs -q");
    mem_size=atoi(argv[2]); 
    shmid=shmget((key_t)label,mem_size,IPC_CREAT|0666);
    if(shmid==-1)
    {
        perror("SHM_MEM-CRE-ERR:");
        msgctl(mqid,IPC_RMID,0);
        exit(1);
    }
    system("ipcs -m");
    s=(sem_t*)shmat(shmid,0,0);
    if(s==NULL)
    {
        perror("SHM-AT-ERR:");
        shmctl(shmid,IPC_RMID,0);
        shmdt(s);
        msgctl(mqid,IPC_RMID,0);
        exit(1);
    }
    printf("\nEnter the initialization value for the semaphore :");
    scanf("%d",&inval);
    rval=sem_init(s,1,inval);
    if(rval==-1)
    {
        perror("Unable to initialize semaphore value:");
        msgctl(mqid,IPC_RMID,0);
        sem_destroy(s);
        shmdt(s);
        shmctl(shmid,IPC_RMID,0);
        exit(1);
    }
    rval=sem_getvalue(s,&sval);
    if(rval==-1)
    {
        perror("Unable to get semaphore value:");
        msgctl(mqid,IPC_RMID,0);
        sem_destroy(s);
        shmdt(s);
        shmctl(shmid,IPC_RMID,0);
        exit(1);
    }
    printf("\nSemaphore value after initialization is %d\n",sval);
    printf("\nEnter the message ID to be used between parent and child: ");
    scanf("%d",&msgid);
    pid=fork();
    if(pid==-1)
    {
        perror("FRK-ERR:");
        msgctl(mqid,IPC_RMID,0);
        sem_destroy(s);
        shmdt(s);
        shmctl(shmid,IPC_RMID,0);
        exit(1);
    }
    if(pid==0)
    {
        message m1;
        printf("\nCHILD : pid = %d\n",getpid());
        rval=sem_wait(s);
        if(rval==-1)
        {
            perror("SEM-WAIT-ERR:");
            msgctl(mqid,IPC_RMID,0);
            sem_destroy(s);
            shmdt(s);
            shmctl(shmid,IPC_RMID,0);
            exit(1);
        }
        printf("\nCHILD : Enter the message to be sent to parent : ");
        scanf("%s",m1.txt);
        m1.id=msgid;
        rval=msgsnd(mqid,(message*)&m1,sizeof(m1),0);
        if(rval==-1)
        {
            perror("MSG-SND-ERR:");
            msgctl(mqid,IPC_RMID,0);
            sem_destroy(s);
            shmdt(s);
            shmctl(shmid,IPC_RMID,0);
            exit(1);
        }       
        rval=sem_post(s);
        if(rval==-1)
        {
            perror("SEM-POST-ERR:");
            msgctl(mqid,IPC_RMID,0);
            sem_destroy(s);
            shmdt(s);
            shmctl(shmid,IPC_RMID,0);
            exit(1);
        }
        exit(1);
    }
    else
    {
        message m2;
        rval=sem_wait(s);
        if(rval==-1)
        {
            perror("SEM-WAIT-ERR:");
            msgctl(mqid,IPC_RMID,0);
            sem_destroy(s);
            shmdt(s);
            shmctl(shmid,IPC_RMID,0);
            exit(1);
        }
        printf("\nPARENT : Waiting to receive message from child\n");
        rval=msgrcv(mqid,(message*)&m2,sizeof(m2),msgid,0);
        if(rval==-1)
        {
            perror("MSG-RCV-ERR:");
            msgctl(mqid,IPC_RMID,0);
            sem_destroy(s);
            shmdt(s);
            shmctl(shmid,IPC_RMID,0);
            exit(1);
        }
        printf("\nPARENT : Message received is : %s\n",m2.txt);
        rval=sem_post(s);
        if(rval==-1)
        {
            perror("SEM-POST-ERR:");
            msgctl(mqid,IPC_RMID,0);
            sem_destroy(s);
            shmdt(s);
            shmctl(shmid,IPC_RMID,0);
            exit(1);
        }
        msgctl(mqid,IPC_RMID,0);
        sem_destroy(s);
        shmdt(s);
        shmctl(shmid,IPC_RMID,0);
    }
}

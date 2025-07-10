#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<sys/types.h>
#include<semaphore.h>
#include<sys/shm.h>
#include<sys/ipc.h>
void main(int argc,char* argv[])
{
    int shmid,rval,sval,csval;
    sem_t *sem_phore;
    system("clear");
    if(argc<3)
    {
        printf("\nUSAGE : %s labelForSHM ByteSize\n",argv[0]);
        exit(0);
    }
    shmid=shmget((key_t)atoi(argv[1]),atoi(argv[2]),IPC_CREAT|0666);
    if(shmid==-1)
    {
        perror("SHM-CRE-ERR:");
        exit(1);
    }
    sem_phore=(sem_t*)shmat(shmid,0,0);
    if(!sem_phore)
    {
        perror("SHM-ATT-ERR:");
        shmctl(shmid,IPC_RMID,0);
        exit(1);
    }
    printf("\nEnter the initial value for the semaphore: ");
    scanf("%d",&sval);
    rval=sem_init(sem_phore,1,sval);
    if(rval==-1)
    {
        perror("Unable to initialize semaphore:");
        shmdt(sem_phore);
        shmctl(shmid,IPC_RMID,0);
        exit(1);
    }
    rval=sem_getvalue(sem_phore,&csval);
    if(rval==-1)
    {
        perror("Unable to get value of the semaphore: ");
        shmdt(sem_phore);
        shmctl(shmid,IPC_RMID,0);
        exit(1);
    }
    printf("\nInitialized value of semaphore is %d\n",csval);
    rval=sem_wait(sem_phore);
    if(rval==-1)
    {
        perror("WAIT-FAILURE:");
        shmdt(sem_phore);
        shmctl(shmid,IPC_RMID,0);
        exit(1);
    }
    rval=sem_getvalue(sem_phore,&csval);
    if(rval==-1)
    {
        perror("Unable to get semaphore value:");
        shmdt(sem_phore);
        shmctl(shmid,IPC_RMID,0);
        exit(1);
    }
    printf("\nSemaphore value after wait is %d\n",csval);
    rval=sem_post(sem_phore);
    if(rval==-1)
    {
        perror("Unable to get semaphore value:");
        shmdt(sem_phore);
        shmctl(shmid,IPC_RMID,0);
        exit(1);
    }
    rval=sem_getvalue(sem_phore,&csval);
    if(rval==-1)
    {
        perror("Unable to get semaphore value: ");
        shmdt(sem_phore);
        shmctl(shmid,IPC_RMID,0);
        exit(1);
    }
    printf("\nSemaphore value after signal operation is %d\n",csval);
    rval=sem_destroy(sem_phore);
    if(rval==-1)
    {
        perror("SEM-DESTROY-ERR:");
        shmdt(sem_phore);
        shmctl(shmid,IPC_RMID,0);
        exit(1);
    }
    rval=shmdt(sem_phore);
    if(rval==-1)
    {
        perror("SHM-DETACH-ERR:");
        shmdt(sem_phore);
        shmctl(shmid,IPC_RMID,0);
        exit(1);
    }
    rval=shmctl(shmid,IPC_RMID,0);
    if(rval==-1)
    {
        perror("SHM-REM-ERR:");
        shmdt(sem_phore);
        shmctl(shmid,IPC_RMID,0);
        exit(1);
    }
    system("ipcs -m");
}

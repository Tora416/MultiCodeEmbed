
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<sys/shm.h>
#include<sys/ipc.h>
#include<fcntl.h>

#include"shm_head.h"

#define SIZE 10

int main()
{
    key_t key;
    int array[10],i,n;
    int shmid;
    struct Memory *shmptr;
    key = ftok(".", 'x');
    printf("key:%d\n",key);
    shmid = shmget(key, sizeof(struct Memory), IPC_CREAT | 0666);
     if (shmid < 0) {
          printf("*** shmget error (server) ***\n");
          exit(1);
     }
     
     shmptr=(struct Memory*)shmat(shmid,NULL,0);
     if ((int) shmptr == -1) {
          printf("*** shmat error (server) ***\n");
          exit(1);
     }
     
     printf("enter the array elements less than 10 numbers and use 999 to stop the number\n");
     while(array[i]!=999)
    {
    for(i=0;i<SIZE;i++)
    {
        scanf("%d",&array[i]);
        n=i;
        if(array[i]==999)
        break;

    }
    }
    float product=1,sum=0;
    for(i=0;i<n;i++)
    {
        sum+=array[i];
        product*=array[i];
    }
    shmptr->status  = NOT_READY;
    shmptr->arr[0]=sum;
    shmptr->arr[1]=product;
    shmptr->arr[2]=sum/n;
     shmptr->status=FILLED;
     printf("please start the client in another window\n");
     while (shmptr->status != TAKEN)
          sleep(1);
    shmdt((void *) shmptr);
    printf("back to server and shared memory detached\n");
     
     shmctl(shmid, IPC_RMID, NULL);
     exit(0);
}

     
     
     
     
     
     
     
#include<stdlib.h>
#include<stdio.h>
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
    int shmid,i;
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
     printf("client attached to shared memory\n");
     printf("sum is %f\n",shmptr->arr[0]);
     printf("product is %f\n",shmptr->arr[1]);
     printf("average is %f\n",shmptr->arr[2]);
     shmptr->status=TAKEN;
     shmdt((void*)shmptr);
     exit(0);
}

    
     
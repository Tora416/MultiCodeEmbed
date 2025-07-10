#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/shm.h>
#include<sys/stat.h>
#include<sys/mman.h>
#include<string.h>
#include<fcntl.h>
#include<string.h>

int main()
{
const char* name="odd_even";
const int SIZE=15*1024;
int shmid;
char words;
void* shmptr;
shmid=shm_open(name,O_CREAT|O_RDWR,0666);
      if (shmid< 0) {
          printf("*** shmget error (server) ***\n");
          exit(1);
     }
     ftruncate(shmid,SIZE);
     shmptr=mmap(0,SIZE,PROT_WRITE,MAP_SHARED,shmid,0);
     printf("inside client\n");
     while(1)
     {
         puts(shmptr);
         shmptr+=15*sizeof(char);
     }
     shm_unlink(name);
     return 0;
}
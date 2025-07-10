#include  <stdio.h>
#include  <stdlib.h>
#include  <sys/mman.h>
#include  <sys/stat.h>
#include  <sys/shm.h>
#include<errno.h>
#include<fcntl.h>
#include<string.h>
#include<sys/wait.h>
#include<unistd.h>

#define GIVE 0
#define TAKE 1

int main()
{
     int     shmid;
     void* shmptr;
     
    const int SIZE=4096;
    const char* name="vowels";
      shmid=shm_open(name,O_CREAT|O_RDWR,0666);
      ftruncate(shmid,SIZE);
      shmptr=mmap(0,SIZE,PROT_WRITE,MAP_SHARED,shmid,0);
      printf("inside client\n");
      
     
      printf("the word count  is:\n");
      
      puts(shmptr);
      printf("the character count  is:\n");
      shmptr+=sizeof(int);
      puts(shmptr);
      shm_unlink(name);
      return 0;
}
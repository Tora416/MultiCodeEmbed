#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/shm.h>
#include<sys/stat.h>
#include<sys/mman.h>
#include<string.h>
#include<fcntl.h>

void choice_zero(char b[10]);
void choice_one(char b[10]);

int main(int argc,char *argv [])
{
    char s[10],b[10];
    int a,n;
    const int SIZE =4096;
    const char* name ="os";
    int key,shmid;
    void* shmptr;
    if (argc<2)
    {printf("enter the format ./'name',stringFFF,choice'1 or 0'");}
    
    
    key=shm_open(name,O_CREAT|O_RDWR,0666);
      if (key < 0) {
          printf("*** shmget error (server) ***\n");
          exit(1);
     }
     ftruncate(key,SIZE);
    shmptr=mmap(0,SIZE,PROT_WRITE,MAP_SHARED,key,0);
    printf("atached to the shared memory\n");
    strcpy(s,argv[1]);
    n=strlen(s);
    sprintf(shmptr,"%d",n-3);
    strcpy(b,s);
    a=atoi(argv[2]);
    if (a==0)
    {choice_zero(b);}
    else if(a==1)
    {choice_one(b);}
    else
    {return 0;}
    sleep(10);
    shmid=munmap(shmptr,SIZE);
    key=shm_unlink(name);
    
    return 1;
}
    
    
    
    void choice_one(char b[10])
{
    char p[10]="SIOSFFF";
    

        if (strcmp(b,p)==0)
        {printf("the value is matching with SIOS\n");}
        else{
        printf("the  string is not matching with SIOS\n");
        }
        
}
    
void choice_zero(char b[10])
{
        char r[10]="MCISFFF";
        if (strcmp(b,r)==0)
        {printf("the value is matching with MCIS\n");}
        else{
        printf("the  string is not matching with MCIS\n");
        }
}
    
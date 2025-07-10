#include  <stdio.h>
#include  <stdlib.h>
#include  <sys/stat.h>
#include  <sys/mman.h>
#include  <sys/shm.h>
#include<errno.h>
#include<fcntl.h>
#include<string.h>
#include<sys/wait.h>
#include<unistd.h>


#define FILESI 20
#define GIVE 0
#define TAKE 1

int read_count(char s[FILESI]);
 int n,m;
int main()
{
    const int SIZE=4096;
    const char* name="vowels";
     int     shmid;
     void* shmptr;
     char s[FILESI];
    
     printf("enter the file path\n");
     scanf("%s",s);
     read_count(s);
     shmid=shm_open(name,O_CREAT|O_RDWR,0666);
     if(shmid<0){
         perror("shmget");
         exit(1);
     }
     ftruncate(shmid,SIZE);
     shmptr=mmap(0,SIZE,PROT_WRITE,MAP_SHARED,shmid,0);
    printf("shared mym attached\n");
    sprintf(shmptr,"%d",m);
    shmptr +=sizeof(int);
    
    sprintf(shmptr,"%d",n);
    shmptr +=sizeof(int);
    
     printf("open client\n");
     
     
     sleep(10);
     
     munmap(shmptr,SIZE);
     shm_unlink(name);
     return 0;
}

int read_count(char s[FILESI])
{
    FILE(*fp);
    fp=fopen(s,"r");
    char ch;
    if (fp==NULL){
        printf("error in opening file\n");
        return 0;
    }
    n=m=0;
    while((ch=fgetc(fp))!=EOF)
    {
        n++;
        if (ch=='\n'||ch=='\t'||ch=='.'||ch==' '||ch=='\0')
        m++;
    }
    
    
    fclose(fp);
    return 1;
}
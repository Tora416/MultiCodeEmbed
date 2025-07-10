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

char words[15];

int main()
{
const char* name="odd_even";
const int SIZE=15*1024;
int shmid;
void* shmptr;
shmid=shm_open(name,O_CREAT|O_RDWR,0666);
      if (shmid< 0) {
          printf("*** shmget error (server) ***\n");
          exit(1);
     }
     ftruncate(shmid,SIZE);
     shmptr=mmap(0,SIZE,PROT_WRITE,MAP_SHARED,shmid,0);
     printf("atached to the shared memory\n");
     
    memset(words,0,sizeof(words));
    char ch;
    int wrd=0,i=0;
    FILE *fp,*fpe,*fpo;
    fp=fopen("input.txt","r");
    fpe=fopen("even.txt","w+");
    fpo=fopen("odd.txt","w+");

    while ((ch = fgetc(fp)) != EOF)
    {
    if (ch == ' ' || ch == '\t' || ch == '\n' || ch == '\0'||ch=='.')
    {
        wrd++;
        if((wrd%2)==0)
        {
            fprintf(fpe,"%s\n",words);
        }
        else
        {
            fprintf(fpo,"%s\n",words);
    }
    memset(words,0,sizeof(words));
    i=0;
    }
    else
    {
    words[i]=ch;
    i=i+1;
    }
    }
    fclose(fp);
    fclose(fpo);
    fclose(fpe);
    printf("i am here\n");
printf("even file opening-----\n");
fpe=fopen("even.txt","r");
sprintf(shmptr,"%s","even_file");
shmptr+=15*sizeof(char);
    
while (fgets(words,sizeof(words),fpe)!=NULL)
{
    sprintf(shmptr,"%s",words);
    shmptr+=15*sizeof(char);
}
fclose(fpe);

printf("odd file opening-----\n");
fpo=fopen("odd.txt","r");
sprintf(shmptr,"%s","odd_file");
shmptr+=SIZE;
printf("fine till\n");
while (fgets(words,sizeof(words),fpo)!=NULL)
{
    sprintf(shmptr,"%s",words);
    shmptr+=15*sizeof(char);
}
fclose(fpo);
sleep(15);
munmap(shmptr,SIZE);
shm_unlink(name);
return 0;
}





#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<ctype.h>
#include<errno.h>

char words[15];
void odd_file_open();
void even_file_open();

int main()
{
    
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
    int pid1,pid2;
    pid1=fork();
    if (pid1==0)
    {
        printf("inside first child\n");
        even_file_open();
    }
    else{
        wait(NULL);
        pid2=fork();
    if (pid2==0)
       {
        printf("inside second child\n");
        odd_file_open();
        }
        else{
            wait(NULL);
            printf("i am done\n");
        }
    }
        return 0;
}
        
void even_file_open()
{
    FILE *fpe;
printf("even file opening-----\n");
fpe=fopen("even.txt","r");
while (fgets(words,sizeof(words),fpe)!=NULL)
{
    printf("\t%s",words);
}
fclose(fpe);
}
void odd_file_open()
{
    FILE *fpo;
printf("odd file opening-----\n");
fpo=fopen("odd.txt","r");
while (fgets(words,sizeof(words),fpo)!=NULL)
{
    printf("\t%s",words);
}
fclose(fpo);
}


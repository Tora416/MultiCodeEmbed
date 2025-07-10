#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<pthread.h>
#include<errno.h>

char words[15];
void *odd_file_open(void *para);
void *even_file_open(void *para);

int main()
{
    
    memset(words,0,sizeof(words));
    char ch;
    int wrd=0,i=0;
    FILE *fp,*fpe,*fpo;
    pthread_t thread1,thread2;
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
    pthread_create(&thread1,NULL,even_file_open,NULL);
    pthread_join(thread1,NULL);
    pthread_create(&thread2,NULL,even_file_open,NULL);
    pthread_join(thread2,NULL);
    printf("\ti am done:) \n");
    
        return 0;
}
        
void *even_file_open(void *para)
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
void *odd_file_open(void *para)
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


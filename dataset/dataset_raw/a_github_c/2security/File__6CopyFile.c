#include<stdio.h>
#include<stdlib.h>
FILE *openfile(char *,char *);
int copyfile(char *,char *);
void main()
    {
    int cf  ;
    
    cf=copyfile("File6To.txt","File6From.txt");
    if(cf==1)
        printf("Copy done");
    else
        printf("Copy not done");
    getch();
    }
int copyfile(char *to,char *from)
    {
    FILE *t,*f;
    int ch;
    t=openfile(to,"w");
    f=openfile(from,"r");
    if(f==NULL||t==NULL)
        return 0;
    while((ch=fgetc(f))!=EOF)
        fputc(ch,t);
    return 1;
    }
FILE *openfile(char *path,char *mode)
    {
    FILE *fp;
    fp=fopen(path,mode);
    if(fp==NULL)
        {
        perror("File opening error (:");
        getch();
        exit(0);
        }
    return fp;
    }






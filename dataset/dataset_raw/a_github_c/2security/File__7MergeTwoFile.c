#include<stdio.h>
#include<stdlib.h>
FILE *openfile(char *,char *);
int mergefile(char *,char *,char *);
void main()
    {
    int cf  ;

    cf=mergefile("File71.txt","File72.txt","File7.txt");
    if(cf==1)
        printf("Merge done");
    else
        printf("Merge not done");
    getch();
    }
int mergefile(char *fp1,char *fp2,char *fp3)
    {
    FILE *one,*two,*three;
    int ch;
    
    one=openfile(fp1,"r");
    two=openfile(fp2,"r");
    three=openfile(fp3,"w");
    
    if(one==NULL||two==NULL||three==NULL)
        return 0;
        
    while((ch=fgetc(one))!=EOF)
        fputc(ch,three);
        
    while((ch=fgetc(two))!=EOF)
        fputc(ch,three);
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

#include<stdio.h>
#include<stdlib.h>
int main()
    {
        FILE *fptr;
        int c=0,word=0,line=0;
        char ch;
        
        if((fptr=fopen("File8.txt","r"))==NULL)
            {
                printf("\n File not exit");
                exit(1);
            }
        while((ch=fgetc(fptr))!=EOF)
            {
                c++;
                if(ch=='\n'||ch=='\0')
                    line++;
                if(ch==' '||ch=='\n'||ch=='\t'||ch==','||ch=='.'||ch==':'||ch==';'||ch=='-')
                    word++;         
            }
        if(c>0)
            {
                line++;
                word++;
            }
        printf("\n Total character:: %d",c);
        printf("\n Total word:: %d",word);
        printf("\n Total line:: %d",line);
        
        fclose(fptr);
        return 0;
    }

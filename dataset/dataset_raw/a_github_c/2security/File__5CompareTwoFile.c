#include<stdio.h>
#include<stdlib.h>
int pos=0,line=1,error=0;
int CompareFile(FILE *fptr1,FILE *fptr2)
    {
    char ch1,ch2;
    int n=1;
    ch1=getc(fptr1);
    ch2=getc(fptr2);
    while(ch1!=EOF&&ch2!=EOF)
        {
        pos++;
        if(ch1 =='\n'&&ch2=='\n') 
            { 
            line++; 
            pos = 0; 
            }    
        
        if(ch1!=ch2)
            {
            n=0;
            error++;
            }
            
        ch1=getc(fptr1);
        ch2=getc(fptr2);
        }
    return n;
    }
int main()
    {
        FILE *fptr1,*fptr2;
        char str[100];
        int n,line,col;
        
        fptr1=fopen("File51.txt","r");
        fptr2=fopen("File52.txt","r");
    
        if(fptr1==NULL||fptr2==NULL)
            {
                perror("File openning error (: ");
                getch();
                exit(0);
            }           
        
        if(CompareFile(fptr1,fptr2))
            printf("\n Two file is same");
        else
            printf("\n Two file is not same error:%d pos:%d line:%d",error,pos,line);
    
        
        fclose(fptr1);
        fclose(fptr2);
        
        return 0;
    }


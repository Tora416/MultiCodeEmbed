#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main()
    {
        FILE *fptr,*fp=NULL;
        int ch;
        fptr=fopen("File18.txt","r");
        fp=fopen("File18Final.txt","w");
        
        if(fptr==NULL||fp==NULL)
            {
                printf("\n Unable to open file");
                exit(1);
            }
        
        while((ch=fgetc(fptr))!=EOF)
            {
                if(isupper(ch))
                    ch=tolower(ch);
                else if(islower(ch))
                    ch=toupper(ch);
                
                fputc(ch,fp);
            }
        
        printf("\n Successfully Toggled");
        fclose(fptr);
        fclose(fp);
        
        remove("File18.txt");
        
        rename("File18Final.txt","File18.txt");
        
        return 0;
    }

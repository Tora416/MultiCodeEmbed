#include<stdio.h>
#include<stdlib.h>
#include<string.h>
void removeWord(char *buffer,char *str)
    {
        int m,n,f,i,j;
        m=strlen(buffer);
        n=strlen(str);
        
        
        
        
    }
int main()
    {
        FILE *fptr1,*fptr2;
        int ;
        char str[1000],buffer[1000];
        
        printf("\n Enter word to remove");
        scanf("%s",str);
        
        fptr1=fopen("File8.txt","r");
        fptr2=fopen("File8Final.tmp","w");
        
        if(ptr1==NULL||ptr2==NULL)
            {
                printf("\n File not exit");
                exit(1);
            }
        
        while((fgets(buffer,1000,fptr1))!=NULL)
            {
            removeWord(buffer,str);
            fputs(buffer,fptr2);
            }
        
        
        fclose(fptr1);
        fclose(fptr2);
        
        remove("File8.txt");
        
        rename("File8.tmp","File8.txt");
        
        printf("\n Successfully removed");
        
        return 0;
    }

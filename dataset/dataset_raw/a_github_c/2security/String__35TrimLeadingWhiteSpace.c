#include<stdio.h>
#include<string.h>
int Mystrlen(char *str)
    {
        int i;
        for(i=0;i<str[i]!=0;i++);
        
        return i;
        
    }

char* Trimleading(char *str)
    {
        int i=0,j,c=0,n;
        char *temp;
        n=Mystrlen(str);
        
        while(str[c]==' '||str[c]=='\t'||str[c]=='\n')
            {
                c++;
            }
    
        for(j=c;j<=n-1;j++)
            {
                str[i]=str[j];  
                
                i++;
            }
        str[i]='\0';
        
        return str;
    }

int main()
    {
        int i,n;
        char str[50];
        printf("\n Enter the string");
        gets(str);
        
        printf("\n Before trimming::");
        printf("%s",str);
        
        printf("\n After trimming::");
        printf("%s",Trimleading(str));
        
        return 0;
    }

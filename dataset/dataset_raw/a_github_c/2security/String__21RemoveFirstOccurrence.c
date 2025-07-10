#include<stdio.h>
#include<string.h>
int main()
    {
        int i,pos,j;
        char str[30],temp[30],ch;
        printf("\n Enter the string");
        gets(str);
        
        printf("\n Enter the character");
        scanf("%c",&ch);
        
        for(i=0;i<str[i]!='\0';i++)
            {
                if(str[i]==ch)
                    {
                        pos=i;
                        break;
                    }
            }
        for(j=0;i<str[j]!='\0';j++);
        
        for(i=pos;i<=j-1;i++)
            str[i]=str[i+1];
            
        str[i]='\0';
        
        printf("%s",str);
        return 0;
    }

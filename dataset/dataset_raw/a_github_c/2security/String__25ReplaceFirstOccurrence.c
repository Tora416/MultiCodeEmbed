#include<stdio.h>
#include<string.h>
int main()
    {
        int i,pos;
        char str[30],ch,rech;
        printf("\n Enter the string");
        gets(str);
        
        printf("\n Enter character to replace");
        ch=getchar();
        
        getchar();
        
        printf("\n Enter character to replace with");
        rech=getchar();
        
        for(i=0;i<str[i]!='\0';i++)
            {
                if(str[i]==ch)
                    {
                        pos=i;
                        str[pos]=rech;
                        break;
                    }
            }
        
        printf("\n After replace %s",str);
        return 0;
    }

#include<stdio.h>
int Noofword(char *str)
    {
    int i=0,word=0;
    char prevchar='\0';
    while(1)
        {
        if(str[i]==' '||str[i]=='\n'||str[i]=='\t'||str[i]=='\0')   
            {
                if(prevchar!=' ' && prevchar!='\n'&&prevchar!='\t'&&prevchar!='\0')
                word++;
            }
        prevchar=str[i];
        if(str[i]=='\0')
            break;
        else 
            i++;
        }
    return word;
    }
int main()
    {
        char str[20];
        int i=0,v=0,c=0;
        printf("\n Enter the string:: ");
        gets(str);
        
        printf("\n No of word in the string is =%d",Noofword(str));
    
        return 0;
    }
    
    

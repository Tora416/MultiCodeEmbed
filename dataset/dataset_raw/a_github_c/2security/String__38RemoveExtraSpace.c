#include<stdio.h>
#include<string.h>
int Mystrlen(char *str)
    {
        int i;
        for(i=0;i<str[i]!=0;i++);
        
        return i;
        
    }

char* RemoreExSpace(char *str)
    {
        int i, j;
    char * newString;
    i=Mystrlen(str);
    newString = (char *)malloc(i);

    i = 0;
    j = 0;

    while(str[i] != '\0')
    {
        
        if(str[i] == ' ')
        {
            newString[j] = ' ';
            j++;

            
            while(str[i] == ' ')
                i++;
        }

        newString[j] = str[i];

        i++;
        j++;
    }
    
    newString[j] = '\0';

    return newString;
    }

int main()
    {
        int i,n;
        char str[50];
        printf("\n Enter the string:");
        gets(str);
        
        printf("\n Before removal of extra space:");
        printf("%s",str);
        
        printf("\n After removal of extra space:");
        printf("%s",RemoreExSpace(str));
        printf("Good bye");
        return 0;
    }

#include<stdio.h>
int Mystrlen(char *str)
    {
        char *s=str;
        while(*str)
            str++;
        return str-s;
    }
char *Mystrrev(char *str)
    {
        char *begin,*end,temp;
        char *rev;
        int n=Mystrlen(str),i;
        
        begin=str;
        end=str;
        for(i=0;i<n-1;i++)
            end++;
        
        for(i=0;i<n/2;i++)
            {
                temp=*end;
                printf("%c ",*end);
                *end=*begin;
                *begin=temp;
                begin++;
                end--;
            }
        return str;
    }
int main()
    {
        char str[30],*t;
        printf("\n Enter the string");
        scanf("%s",str);
        
        printf("\n Reverse of the string is:: ");
        t=Mystrrev(str);
        puts(t);
    }


#include<stdio.h>
#include<malloc.h>
int Mystrlength(char *str)
    {
        int i;
        for(i=0;i<str[i]!='\0';i++);
        return i;   
    }
char * ReverseWord(char str[])
    {
        int d,s,k=0,t,j;
        char *temp= malloc(Mystrlength(str));
        s=Mystrlength(str)-1;
        d=Mystrlength(str)-1;
        while(s>0)
            {
            if(str[s]== ' ')    
                {
                    for(j=s+1;j<=d;j++)
                        {
                            temp[k]=str[j];     
                            k++;
                        }
                    temp[k++]=' ';
                    d=s-1;
                }
            s--;
            }
        for(j=0;j<=d;j++)
            {
                temp[k]=str[j]; 
                k++;    
            }
        temp[k]= '\0';
        return temp;
    }
int main()
    {
        char str[20],*temp;
        int n,s,d,k=0;
        printf("\n Enter the string:: ");
        gets(str);
        
        temp=ReverseWord(str);
        printf("Reverse Ordered words is::%s",temp);
    
        return 0;
    }
    
    

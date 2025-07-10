#include<stdio.h>
#define size 255
int MyMax(int a[],int n)
    {
        int i,max=0;
        for(i=0;i<n;i++)
            {
                if(a[i]>a[max])
                    {
                        max=i;
                    }   
            }
        printf("%d",max);
        return max;
    }

int main()
    {
        int freq[size],i,c=0,t;
        char str[size],ch;
        printf("\n Enter the string");
        gets(str);
        
        for(i=0;i<size;i++)
                freq[i]=0;
                
        for(i=0;i<str[i]!='\0';i++)
            {
                t=(int)str[i];
                freq[t]=freq[t]+1;
            }
                
        
        for(i=0;i<size;i++)
            printf("%d ",freq[i]);
            
        i=MyMax(freq,size);
        printf("\n No of occurrence of '%c' is =%d",i,freq[i]);
        return 0;
    }

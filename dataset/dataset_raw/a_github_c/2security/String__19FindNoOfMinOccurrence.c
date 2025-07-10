#include<stdio.h>
#define size 255
int MyMin(int a[],int n)
    {
        int i,min=0;
        for(i=0;i<n;i++)
            {
                if(a[i]!=0)
                    {
                    if(a[i]<a[min]||a[min]==0)
                        min=i;
                    }
                    
            }
        return min;
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
            
        i=MyMin(freq,size);
        printf("\n No of occurrence of '%c' is =%d",i,freq[i]);
        return 0;
    }

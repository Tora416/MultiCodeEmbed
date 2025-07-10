#include<stdio.h>
int Mystrcompare(char *str1,char *str2)
    {
    int m=Mystrlen(str1),flag=0,i;
    int n=Mystrlen(str2);
    
    if(m>n)
        return m-n;
    else if(m<n)
        return m-n;
    else 
        {
        for(i=0;i<m;i++)
            {
                if(str1[i]!=str2[i])
                    {
                        flag=1;
                        break;
                    }
            }
            if(flag==0)
                return 0;
            else 
                return 1;
        }
    
    }
int Mystrlen(char *str)
    {
        int i;
        for(i=0;i<str[i]!='\0';i++);
        
        return i;
    }
int main()
    {
        char str1[20],str2[20];
        int i=0,len1,j=0,k;
        printf("\n Enter the first string");
        gets(str1);
        printf("\n Enter the second string");
        gets(str2);
        
        
        printf("\n Mystrcompare(%s,%s)=%d",str1,str2,Mystrcompare(str1,str2));
        return 0;
    }
    
    

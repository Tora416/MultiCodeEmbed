#include<stdio.h>
#include<string.h>
int main()
    {
        int i,j,k=0,n,m;
        char name[20];
        printf("Enter Name");
        gets(name);
        printf("Enter value of n");
        scanf("%d",&n);
        m=strlen(name);
        
        for(i=n/2;i<n;i=i+2)
            {
                for(j=1;j<n-i;j=j+2)
                    printf(" ");
                for(j=1;j<=i;j++)
                    printf("*");
                for(j=1;j<=i-4*k;j++)
                    printf(" ");
                for(j=1;j<=i;j++)
                    printf("*");
            k++;
                printf("\n");
            }
        for(i=n;i>=1;i--)
            {
                for(j=1;j<=n-i;j++)
                    printf(" "); 
                if(i==n)
                    {
                    for(j=1;j<=(n*2-m)/2;j++)   
                        printf("*");
                    printf("%s",name);
                    for(j=1;j<(n*2-m)/2;j++)    
                        printf("*");
                    }
                else
                    {
                    for(j=1;j<=2*i-1;j++)
                        printf("*");    
                    }
                printf("\n");
            }
        printf("\n");
        return 0;
        
    }

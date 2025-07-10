#include<stdio.h>       

int main()
    {
    int n,i,j;
    
    printf("Enter how many row");
    scanf("%d",&n);
    
    for(i=1;i<=n;i++)
        {
        for(j=1;j<i;j++)
            printf(" ");
        
        for(j=1;j<=n;j++)
            {
                if(i==1||i==n||j==1||j==n)
                    printf("*");
                else
                    printf(" ");
            }
        printf("\n");
        }

    printf("\n\n");
        return 0;
    }   








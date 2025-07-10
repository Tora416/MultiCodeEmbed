#include<stdio.h>       

int main()
    {
    int n,i,j;
    
    printf("Enter how many row");
    scanf("%d",&n);
    
    for(i=1;i<=n;i++)
        {
        for(j=1;j<=2*n-1;j++)   
            {
            if(i+j>=n+1&&i+j<2*n+1)
                {
                printf("*");
                }
            else 
                printf(" ");
            }   
        printf("\n");
        }

    printf("\n\n");
        return 0;
    }   








#include<stdio.h>
int main()
    {
        int n,i,j,k;
        printf("Enter no of rows");
        scanf("%d",&n);
        
        for(i=1;i<=n;i++)
            {
                for(j=n;j>=i;j--)
                    printf("*");
                for(j=2;j<2*i;j++)
                    printf(" ");
                for(j=1;j<=n-i+1;j++)
                    printf("*");
                printf("\n");
            }
        for(i=1;i<=n;i++)
        {
            for(j=1;j<=i;j++)
                printf("*");
            for(j=1;j<=2*n-2*i;j++)
                printf(" ");
            for(j=1;j<=i;j++)
                printf("*");
        printf("\n");
        }
    printf("\n\n");
    return 0;
    }

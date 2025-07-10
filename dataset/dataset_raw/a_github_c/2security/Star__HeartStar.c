#include<stdio.h>
int main()
    {
        int i,j,k=0,n;
        printf("Enter value of n");
        scanf("%d",&n);
        
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
                for(j=1;j<=2*i-1;j++)
                    printf("*");
                printf("\n");
            }

        printf("\n");
        return 0;
        
    }

#include<stdio.h>       

int main()
    {
    int n,i,j,k;
    
    printf("Enter how many row");
    scanf("%d",&n);
    
    for(i=n;i>=1;i--)
        {
        for(j=n;j>i;j--)
            printf(" ");
        for(j=1;j<=2*i-1;j++)
            {
                if(j==2*i-1||j==1||i==n)
                    printf("*");
                else
                    printf(" ");
            }
        printf("\n");
        }
    printf("\n\n");
        return 0;
    }   








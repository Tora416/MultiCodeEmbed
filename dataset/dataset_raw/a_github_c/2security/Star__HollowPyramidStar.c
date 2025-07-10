#include<stdio.h>       

int main()
    {
    int n,i,j,k;
    
    printf("Enter how many row");
    scanf("%d",&n);
    
    for(i=1;i<=n;i++)
        {
        for(j=1;j<=n-i;j++)
            printf(" ");
        for(k=1;k<=2*i-1;k++)
            {
                if(k==1||i==n||k==2*i-1)
                    printf("*");
                else
                    printf(" ");
            }
        printf("\n");
        }
    printf("\n\n");
        return 0;
    }   








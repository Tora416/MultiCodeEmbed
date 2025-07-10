#include<stdio.h>       

int main()
    {
    int n,i,j,k,f;
    
    printf("Enter how many columns");
    scanf("%d",&n);
    f=1;
    
    for(i=1;i<=2*n-1;i++)
        {
            for(j=1;j<=f;j++)   
                printf("*");
            if(i<n)
                f++;
            else
                f--;
        printf("\n");
        }
        
    printf("\n\n");
        return 0;
    }   








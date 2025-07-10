#include<stdio.h>       

int main()
    {
    int n,i,j,k,f;
    
    printf("Enter how many columns");
    scanf("%d",&n);
    f=1;
    
    for(i=1;i<=2*n-1;i++)
        {
            
            if(i<=n)
                {
                f++;
                for(j=1;j<=n-i;j++) 
                    printf(" ");
                }
            else
                {
                f--;
                for(j=1;j<=i-n;j++) 
                    printf(" ");
                }
            for(j=1;j<f;j++)    
                printf("*");
        printf("\n");
        }
        
    printf("\n\n");
        return 0;
    }   








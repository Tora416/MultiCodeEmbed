#include<stdio.h>
int main()
    {
        int n,i,j,k,c=1;
        printf("Enter no of rows");
        scanf("%d",&n);
        
        for(i=1;i<=2*n-1;i++)
            {
                if(i<=n)
                    {
                        for(j=1;j<=n-i;j++)
                            printf(" ");
                            
                        for(j=1;j<=2*i-1;j++)
                            printf("*");
                    }
                else
                    {
                    for(j=i-n;j>=1;j--) 
                        printf(" ");
                        
                    for(j=1;j<=2*(i-2*c)-1;j++)
                        printf("*");
                    c++;
                    }
            printf("\n");
            }
    printf("\n\n");
    return 0;
    }





























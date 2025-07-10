#include<stdio.h>
int main()
{
    int n;
    printf("enter the no. of coins:");
    scanf("%d",&n);
    int coins[n-1];
    int i,count,j;
    printf("The coins are:\n");
    for(i=0;i<n-1;i++)
    {
        scanf("%d",&coins[i]);
    }
    for(i=0;i<n-1;i++)
    {                                        
        count = 0;
        for(j=0;j<n-1;j++)
        {
            if(coins[i] == coins[j])
            {
                count+=1;;
            }
        }
        printf("Mising coin is:");
        if(count%2==1)
        {
            printf("%d",coins[i]);
            return 0;
        }
    }
    return 0;
}

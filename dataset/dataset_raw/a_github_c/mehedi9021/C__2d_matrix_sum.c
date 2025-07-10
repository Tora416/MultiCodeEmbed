#include<stdio.h>
int main()
{
    int a[5][5];
    int r, c;
    for(r=0; r<=1; r++)
    {
        for(c=0; c<=1; c++)
        {
            scanf("%d", &a[r][c]);
        }
        printf("\n");
    }
    for(r=0; r<=1; r++)
    {
        for(c=0; c<=1; c++)
        {
            printf("%d ", a[r][c]);
        }
        printf("\n");
    }
    int sum=0;
    for(r=0; r<=1; r++)
    {
        sum=0;
        for(c=0; c<=1; c++)
        {
            sum=sum+a[r][c];
        }
        printf("\nsum of element of row%d=%d ",r+1, sum);
    }
    for(c=0; c<=1; c++)
    {
        sum=0;
        for(r=0; r<=1; r++)
        {
            sum=sum+a[r][c];
        }
        printf("\nsum of element of coloumn %d=%d ",c+1, sum);
    }
    return 0;
}

#include<stdio.h>
int main()
{
    int i,n;
    printf("Enter the element of array:");
    scanf("%d", &n);
    int a[n];
    for(i=0; i<=n-1; i++)
    {
        scanf("%d", &a[i]);
    }
    printf("\nEven numbers:");
    for(i=0; i<=n-1; i++)
    {
        if(a[i]%2==0)
        {
            printf("%d ", a[i]);
        }
    }
    printf("\n\nOdd numbers:");
    for(i=0; i<=n-1; i++)
    {
        if(a[i]%2==1)
        {
            printf("%d ", a[i]);

        }
    }
    return 0;
}

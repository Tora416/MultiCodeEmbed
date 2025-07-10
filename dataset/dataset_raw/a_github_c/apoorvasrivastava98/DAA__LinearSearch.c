#include <stdio.h>
int main()
{
    int a[100];
    int n,i,count=0,item;
    printf("Enter the size of array");
    scanf("%d",&n);
    printf("Enter the numbers in array \n");
    for(i=0;i<n;i++)
    {
        scanf("%d",&a[i]);
    }
    printf("The elements in array are: \n");
     for(i=0;i<n;i++)
    {
        printf("%d",a[i]);
    }
    printf("Enter the no. to be searched \n");
    scanf("%d",&item);
    count++;
    for(i=0;i<n;i++)
    {
        count++;
        if(a[i]==item)
        {
            count++;
            printf("\n Number found at position %d \n",i);
            count++;
            break;
        }
        count++;
    }
    if(i==n)
    {
        printf("No.not found");  
    }
    printf("Count=%d",count);
}

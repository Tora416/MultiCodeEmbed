#include<stdio.h>
int bubbleSort(int x[],int y);
int main()
{
    int n;
    printf("enter the no. of elements:");
    scanf("%d",&n);
    int arr[n];
    int i;
    printf("enter the elements:");
    for(i=0;i<n;i++)
    {
        scanf("%d",&arr[i]);
    }
    bubbleSort(arr,n);
    return 0;
}
int bubbleSort(int x[],int y)
{
    int i,j,temp;
    for(i=0;i<y;i++)
    {
        for(j=0;j<y-i-1;j++)
        {
            if(x[j] > x[j+1])
            {
                temp = x[j];
                x[j] = x[j+1];
                x[j+1] = temp;
            }
        }
    }
    printf("sorted array:\n");
    for(i=0;i<y;i++)
    {
        printf("%d\n",x[i]);
    }
}

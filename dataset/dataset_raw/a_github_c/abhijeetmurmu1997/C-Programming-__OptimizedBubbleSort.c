#include<stdio.h>
int bubbleSortOptimized(int a[],int n);
int main()
{
    int z,res;
    printf("enter the no.of elements:");
    scanf("%d",&z);
    int arr[z];
    int i;
    printf("the elements are:\n");
    for(i=0;i<z;i++)
    {
        scanf("%d",&arr[i]);
    }
    res = bubbleSortOptimized(arr,z);               
    return 0;                                     
int bubbleSortOptimized(int a[], int n)            
{
    int i,j,temp,flag=0;                           
    for(i=0;i<n;i++)                               
    {
        for(j=0;j<n-i-1;j++)
        {
            if(a[j] > a[j+1])
            {
                temp = a[j];
                a[j] = a[j+1];
                a[j+1] = temp;
                flag += 1;
            }
        }
        if(flag == 0)
        {
            break;
        }
    }
    printf("Sorted array is:\n");
    for(i=0;i<n;i++)
    {
        printf("%d \n",a[i]);
    }
    
}





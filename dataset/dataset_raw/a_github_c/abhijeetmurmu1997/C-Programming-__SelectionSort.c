#include<stdio.h>
int selectionSort(int x[], int n);
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
    res = selectionSort(arr,z); 
    return 0;
}
int selectionSort(int x[], int n)              
{                                              
    int i,j,temp;                              
    for(i=0;i<n;i++)                           
    {
        for(j=i+1;j<n;j++)
        {
            if(x[i] > x[j])
            {
                temp = x[j];
                x[j] = x[i];
                x[i] = temp;
            }
        }
    }
    printf("sorted array:\n");
    for(i=0;i<n;i++)
    {
        printf("%d\n",x[i]);
    }
}

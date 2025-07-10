
#include <stdio.h>
#include <stdlib.h>

void swap(int *x, int *y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
}

void rearrange(int *arr, int n)
{
    int i = -1, j = 0;
    int t;
    while (j != n)
    {
        if (arr[j] % 2 == 0)
        {
            i++;
            
            swap(&arr[i], &arr[j]);
        }
        j++;
    }
}
int main()
{
    int *arr;
    int n;
    printf("Enter number of elements : ");
    scanf("%d", &n);
    arr = (int*)malloc(n*sizeof(int));

    for(int i = 0 ; i < n ; i++)
    {
        printf("Enter element no %d :", i+1);
        scanf("%d", arr + i);
    }
    printf("Original array : \n");
    for(int i = 0 ; i < n ; i++)
    {
        printf("%d ", arr[i]);
    }

    rearrange(arr, n);
    printf("\nRearranged array : \n");
    for(int i = 0 ; i < n ; i++)
    {
        printf("%d ", arr[i]);
    }
}
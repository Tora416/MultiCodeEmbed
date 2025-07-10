

#include <stdio.h>
#include <stdlib.h>

void swap(int *x, int *y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
}

void segregate (int *arr, int n)
{
    int i = 0;
    int j = n - 1;
    while(i < j)
    {
        while(arr[i] == 0 && i < j)
        i++;

        while(arr[j] == 1 && i < j)
        j--;

        if(arr[i] != 0 && arr[j] != 1 && i < j)
        {
            swap(&arr[i], &arr[j]);
            i++;
            j--;
        }
    }
}

int main()
{
    int *arr, n;
    printf("Enter number of elements : ");
    scanf("%d", &n);
    arr = (int*)malloc(n*sizeof(int));
    for(int i = 0 ; i < n ; i++)
    {
        printf("Enter element %d : ", i+1);
        scanf("%d", &arr[i]);
    }
    segregate(arr, n);
    printf("Segregated array : \n");
    for(int i = 0 ; i < n ; i++)
    {
        printf("%d ", arr[i]);
    }

}
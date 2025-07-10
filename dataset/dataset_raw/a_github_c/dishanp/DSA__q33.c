
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
    int i = 0, j = n-1;
    while (i < j)
    {
        while (arr[i]%2 == 0 && i < j)
            i++;

        while (arr[j]%2 == 1 && i< j)
            j--;

        if (i < j)
        {
            swap(&arr[i], &arr[j]);
            i++;
            j--;
        }
    }
}

int main()
{
    int *arr;
    int n;
    printf("Enter number of elements : ");
    scanf("%d", &n);
    arr = (int*)malloc(n*sizeof(int));

    for(int l = 0 ; l < n ; l++)
    {
        printf("Enter element no %d :", l+1);
        scanf("%d", arr + l);
    }

    rearrange(arr, n);
    printf("Rearranged array : \n");
    for(int m = 0 ; m < n ; m++)
    {
        printf("%d", *(arr + m));
    }
    printf("\n");
}
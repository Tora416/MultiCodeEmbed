
#include <stdio.h>
#include <stdlib.h>

void rearrange( int *arr, int n)
{
    int *aux =(int*)malloc(n*sizeof(int));
    for(int i = 0 ; i < n ; i++)
    {
        if(i == 0)
        *(aux + i) = *(arr + i) * (*(arr + i+1));
        else if(i == (n - 1))
        *(aux + i) = *(arr + i) * (*(arr + i-01));
        else
        *(aux + i) = (*(arr + i-1))  * (*(arr + i + 1));
    }
    for(int i = 0 ; i < n ; i++)
    {
        *(arr + i) = *(aux + i);
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
    rearrange(arr, n);
    for (int i = 0 ; i < n ; i++)
    {
        printf("%d ", *(arr + i));
    }
}

#include <stdio.h>
#include <stdlib.h>

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
    int max = arr[0];
    int c = 0;
    for(int i = 0 ; i < n ; i++)
    {
        if(max == arr[i])
        {
            c++;
        }
        if(max < arr[i])
        {
            max = arr[i];
        }
    }
    printf("Largest element is %d and it appears %d times\n", max, c);

}
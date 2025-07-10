


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
    int min1 = *arr;
    int max1 = *arr;
    int min2 = *arr;
    int max2 = *arr;
    for(int i = 0 ; i < n ; i++)
    {
        if(max1 < *(arr + i))
        {
            max2 = max1;
            max1 = *(arr + i);
        }
        
        else if(max2 < *(arr +i) && *(arr +i) != max1)
        {
            max2 = *(arr +i);
        }
        if(min1 > *(arr +i))
        {
            min2 = min1;
            min1 = *(arr + i);
        }
        else if(min2 > *(arr +i) && *(arr +i) != min1)
        {
            min2 = *(arr +i);
        }
    }
    printf("Second smallest element : %d\n", min2);
    printf("Second largest element : %d\n", max2);
}
#include <stdio.h>

int* bsearch(int* first, int size, int x)
{
    int* last = first + size - 1;

    while(first <= last)
    {
        int *mid = first + (last - first)/2;

        if(*mid == x)
            return mid;

        else if(*mid > x)
            last = mid - 1;

        else if(*mid < x)
            first = mid + 1;
    }

    return NULL;
}

int main()
{
    int arr[20];
    int n;
    int toSearch;

    printf("Enter array size: ");
    scanf("%d", &n);

    printf("Enter array elements in sorted order: ");
    for(int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    printf("Enter element to be searched: ");
    scanf("%d", &toSearch);

    if(bsearch(arr, n, toSearch) != NULL)
    {
        int pos = bsearch(arr, n, toSearch) - arr + 1;
        printf("Element found at %dth position. \n \n", pos);
    }

    else
        printf("Element not found \n\n");

    printf("Use of Double pointers. Enter a two numbers:");
    int a, b;
    scanf("%d %d", &a, &b);
    
    int *p1 = &a;
    int **p2 = &p1;

    int *p3 = &b;
    int **p4 = &p3;


    printf("Product = %d \n \n", **p2 * **p4);

}
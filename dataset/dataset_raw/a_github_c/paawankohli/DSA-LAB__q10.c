#include <stdio.h>

void reverse(int arr[], int size)
{
    int *start = arr , *end = arr + size - 1;

    for(int i = 0 ; i < size/2 ; i++)
    {
        int temp = *(start + i);
        *(start + i) = *(end - i);
        *(end - i) = temp;
    }
}

int main()
{
    int a[50], n;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    printf("Enter elements: ");

    for(int i = 0 ; i < n ; i++)
        scanf("%d", &a[i]);

    reverse(a, n);

    for(int i = 0 ; i < n ; i++)
        printf("%d  ", a[i]);

}
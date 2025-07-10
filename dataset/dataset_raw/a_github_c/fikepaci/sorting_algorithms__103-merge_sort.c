#include "sort.h"


void merge_sort(int *array, size_t size)
{
    int low;
    int high;
    int *temp;

    low = 0;
    high = size - 1;

    temp = malloc(sizeof(int) * size);
    if (temp == NULL)
        return;

    sort(array, low, high, temp);

    free(temp);
}


void sort(int *array, int low, int high, int *temp)
{
    int mid;

    if (low < high)
    {
        mid = (low + high) / 2;
        sort(array, low, mid, temp);
        sort(array, mid + 1, high, temp);
        merge(array, low, mid, high, temp);
    }
}


void merge(int *array, int low, int mid, int high, int *temp)
{
    int left;
    int right;
    int i;

    left = low;
    right = mid + 1;

    printf("Merging...\n");
    printf("[left]: ");
    print_array(&array[low], mid + 1);
    printf("[right]: ");
    print_array(&array[mid + 1], high - mid);

    for (i = low; left <= mid && right <= high; i++)
    {
        if (array[left] <= array[right])
            temp[i] = array[left++];
        else
            temp[i] = array[right++];
    }

    while (left <= mid)
        temp[i++] = array[left++];

    while (right <= high)
        temp[i++] = array[right++];

    for (i = 0; i <= high; i++)
        array[i] = temp[i];

    printf("[Done]: ");
    print_array(temp, i);
}


int len(int *array)
{
    int i;

    for (i = 0; array[i] != '\0'; i++)
        ;

    return (i);
}

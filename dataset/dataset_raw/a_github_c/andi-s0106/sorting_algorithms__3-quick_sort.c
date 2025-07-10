#include "sort.h"

int partition(int *array, int lo, int hi, size_t size)
{
    int i, j, pivot, tmp;

    pivot = array[hi];
    i = lo;
    j = lo;
    while (j < hi)
    {
        if (array[j] <= pivot)
        {
            if (i != j)
            {
                tmp = array[i];
                array[i] = array[j];
                array[j] = tmp;
                print_array(array, size);
            }
            i++;

        }
        j++;
    }
    if (i != hi)
    {
        tmp = array[i];
        array[i] = array[hi];
        array[hi] = tmp;
        print_array(array, size);
    }
    return (i);
}

void quicksort(int *array, int lo, int hi, size_t size)
{
    int q;

    if (lo < hi)
    {
        q = partition(array, lo, hi, size);
        quicksort(array, lo, q - 1, size);
        quicksort(array, q + 1, hi, size);
    }

}


void quick_sort(int *array, size_t size)
{
    if (array == NULL || size < 2)
        return;
    quicksort(array, 0, size - 1, size);
}

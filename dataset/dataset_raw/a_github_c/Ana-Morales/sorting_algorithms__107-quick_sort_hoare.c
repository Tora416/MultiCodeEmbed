#include "sort.h"

int partition(int *array, int lo, int hi, size_t size)
{
    int i, j, pivot, tmp;

    pivot = array[hi];
    i = lo - 1;
    j = hi + 1;
    while (1)
    {
        while (array[++i] < pivot)
        {
            ;
        }
        while (array[--j] > pivot)
        {
            ;
        }
        if (i > j)
            return (j);
        if (i != j)
        {
            tmp = array[i];
            array[i] = array[j];
            array[j] = tmp;
            print_array(array, size);
        }

    }
}

void quicksort_hoare(int *array, int lo, int hi, size_t size)
{
    int p;

    if (lo < hi)
    {
        p = partition(array, lo, hi, size);
        quicksort_hoare(array, lo, p, size);
        quicksort_hoare(array, p + 1, hi, size);
    }

}


void quick_sort_hoare(int *array, size_t size)
{
    if (array == NULL || size < 2)
        return;
    quicksort_hoare(array, 0, size - 1, size);
}

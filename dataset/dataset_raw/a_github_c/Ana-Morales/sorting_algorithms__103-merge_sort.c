#include "sort.h"
#include <stdio.h>
#include <stdlib.h>

void TopDownMerge(int *copy, int begin, int middle, int end, int *array)
{
    int i, j, k;

    i = begin;
    j = middle;
    k = begin;
    printf("Merging...\n");
    printf("[left]: ");
    print_array(&copy[begin], middle - begin);
    printf("[right]: ");
    print_array(&copy[middle], end - middle);
    while (k < end)
    {
        if (i < middle && (j >= end || copy[i] <= copy[j]))
        {
            array[k] = copy[i];
            i++;
        }
        else
        {
            array[k] = copy[j];
            j++;
        }
        k++;
    }
    printf("[Done]: ");
    print_array(&array[begin], end - begin);
}

void TopDownSplitMerge(int *copy, int begin, int end, int *array)
{
    int middle;

    if (end - begin <= 1)
        return;
    middle = (end + begin) / 2;
    TopDownSplitMerge(array, begin, middle, copy);
    TopDownSplitMerge(array, middle, end, copy);
    TopDownMerge(copy, begin, middle, end, array);
}


void merge_sort(int *array, size_t size)
{
    int *copy;
    size_t i;

    if (array == NULL || size < 2)
        return;
    copy = malloc(sizeof(int) * size);
    if (!copy)
        return;
    i = 0;
    while (i < size)
    {
        copy[i] = array[i];
        i++;
    }
    TopDownSplitMerge(copy, 0, (int)size, array);
    free(copy);
}

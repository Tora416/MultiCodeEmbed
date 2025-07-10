#include "sort.h"
#include <stdlib.h>
void swap(int *array, int gap, int idx);



void shell_sort(int *array, size_t size)
{
    int limit;
    int idx;
    int gap;
    int up;

    if (size < 2)
        return;
    up = (int) size;
    for (gap = 1; gap < up / 3; gap = gap * 3 + 1)
    {}

    for (limit = 0; limit < up;)
    {
        idx = limit;

        while (idx < up)
        {
            if (idx + gap < up && array[idx] > array[idx + gap])
                swap(array, gap, idx);
            idx = idx + gap;
        }
        limit++;
        if (limit == gap)
        {
            gap = gap / 3;
            limit = 0;
            print_array(array, size);
        }
        if (gap < 1)
            break;
    }
}


void swap(int *array, int gap, int idx)
{
    int tmp;

    tmp = array[idx];
    array[idx] = array[idx + gap];
    array[idx + gap] = tmp;
    idx = idx - gap;
    while (idx >= 0)
    {
        if (array[idx] > array[idx + gap])
        {
            tmp = array[idx];
            array[idx] = array[idx + gap];
            array[idx + gap] = tmp;
        }

        idx = idx - gap;
    }
}

#include "sort.h"


void _swap(int *a, int *b)
{
    int tmp;

    tmp = *a;
    *a = *b;
    *b = tmp;
}

void backward_insertion(int *array, int gap, int act)
{
    int i;

    for (i = act - gap; i >= 0; i -= gap, act -= gap)
    {
        if (array[i] > array[act])
            _swap(&array[i], &array[act]);
        else
            break;
    }
}

void shell_sort(int *array, size_t size)
{
    unsigned int gap = 1, i, j;

    if (array == NULL)
        return;
    if (size < 2)
        return;
    while (gap < size / 3)
        gap = gap * 3 + 1;

    while (gap > 0)
    {
        for (i = 0, j = gap; j < size; i++, j++)
        {
            if (array[i] > array[j])
            {
                _swap(&array[i], &array[j]);
                backward_insertion(array, gap, i);
            }
        }
        print_array(array, size);
        gap /= 3;
    }
}

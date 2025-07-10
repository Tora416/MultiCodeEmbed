#include "sort.h"
#include <stdlib.h>

void counting_sort(int *array, size_t size)
{
    int *count = NULL, *out = NULL, max = 0, total = 0;
    size_t i, j;

    if (array == NULL || size < 2)
        return;
    for (i = 0; i < size; i++)
    {
        if (array[i] > max)
            max = array[i];
    }
    count = malloc(sizeof(int) * (max + 1));
    if (!count)
        return;
    j = max;
    for (i = 0; i <= j; i++)
        count[i] = 0;
    for (i = 0; i < size; i++)
        count[array[i]]++;
    for (i = 0; i <= j; i++)
    {
        total += count[i];
        count[i] = total;
    }
    print_array(count, max + 1);
    out = malloc(sizeof(int) * size);
    if (!out)
    {
        free(count);
        return;
    }
    for (i = 0; i < size; i++)
    {
        out[--count[array[i]]] = array[i];
    }
    for (i = 0; i < size; i++)
        array[i] = out[i];
    free(out);
    free(count);
}

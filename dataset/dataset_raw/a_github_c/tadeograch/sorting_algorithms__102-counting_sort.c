#include "sort.h"


void counting_sort(int *array, size_t size)
{
    int i, j, max = 0;
    int *new_arr, *new_new;

    if (size < 2)
        return;

    for (i = 0; i <= (int)size; i++)
    {
        if (array[i] > max)
            max = array[i];
    }
    max += 1;
    new_arr = (int *) malloc(sizeof(int) * max);
    for (i = 0; i <= max; i++)
        new_arr[i] = 0;

    for (i = 0; i < (int)size; i++)
        new_arr[array[i]] += 1;

    for (i = 0; i < max; i++)
    {
        j = i + 1;
        new_arr[j] += new_arr[i];
    }
    print_array(new_arr, max);

    new_new = malloc(sizeof(int) * size);

    for (i = 0; i < (int)size; i++)
    {
        new_arr[array[i]] -= 1;
        new_new[new_arr[array[i]]] = array[i];
    }
    for (i = 0; i < (int)size; i++)
        array[i] = new_new[i];

    free(new_new);
    free(new_arr);
}

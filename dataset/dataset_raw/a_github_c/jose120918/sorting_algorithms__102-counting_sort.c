#include "sort.h"


void counting_sort(int *array, size_t size)
{
    int max, position, *count = NULL, *order = NULL;
    size_t i;

    if (size < 2 || array == NULL)
        return;
    
    max = array[0];
    for (i = 0; i < size; i++)
        if (array[i] > max)
            max = array[i];
    
    count = malloc(sizeof(int) * (max + 1));
    for (i = 0; i <= (size_t)max; i++)
        count[i] = 0;
    
    for (i = 0; i < size; i++)
        count[array[i]] = count[array[i]] + 1;
    
    for (i = 1; i <= (size_t)max; i++)
        count[i] = count[i] + count[i - 1];
    print_array(count, (size_t)max + 1);
    
    order = malloc(sizeof(int) * size);
    for (i = 0; i < size; i++)
    {
        count[array[i]] = count[array[i]] - 1;
        position = count[array[i]];
        order[position] = array[i];
    }
    
    for (i = 0; i < size; i++)
        array[i] = order[i];
    free(count);
    free(order);
}
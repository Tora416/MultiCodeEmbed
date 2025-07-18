#include "sort.h"

void selection_sort(int *array, size_t size)
{
    size_t boundary = 0, min_pos, i;
    int min, temp;

    while (boundary < size)
    {
        i = boundary;
        min = array[boundary];
        min_pos = boundary;
        while (i < size)
        {
            if (array[i] < min)
            {
                min = array[i];
                min_pos = i;
            }
            i++;
        }
        if (min_pos != boundary)
        {
            temp = array[boundary];
            array[boundary] = array[min_pos];
            array[min_pos] = temp;
            print_array(array, size);
        }
        boundary++;
    }
}

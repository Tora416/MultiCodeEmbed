
#include "sort.h"


void shell_sort(int *array, size_t size)
{
    size_t h = 1, i, n;
    int number;

    if (!size || !array)
        return;

    while (h < size)
        h = 3 * h + 1;

    h = (h - 1) / 3;

    while (h > 0)
    {
        for (i = h; i < size; i++)
        {
            number = array[i];
            for (n = i; n > h - 1 && array[n - h] > number; n = n - h)
            {
                array[n] = array[n - h];
            }
            array[n] = number;
        }
        h = h / 3;
        print_array(array, size);
    }
}
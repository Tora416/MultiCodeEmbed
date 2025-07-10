#include "sort.h"

void shell_sort(int *array, size_t size)
{

    int value;
    size_t i, j, gap;

    if (array == NULL || size < 2)
        return;
    gap = 1;
    while (gap < size / 3)
    {
        gap = (gap * 3) + 1;
    }
    while (gap > 0)
    {
        i = gap;
        while (i < size)
        {
            value = array[i];
            j = i;
            while (j > gap - 1 && array[j - gap] >= value)
            {
                array[j] = array[j - gap];
                j -= gap;
            }
            array[j] = value;
            i++;
        }
        gap = (gap - 1) / 3;
        print_array(array, size);
    }
}

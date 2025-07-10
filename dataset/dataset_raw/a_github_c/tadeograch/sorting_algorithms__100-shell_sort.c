#include "sort.h"



void shell_sort(int *array, size_t size)
{
    size_t n = 0, i, j;
    int temp = 0;

    if (size < 2)
        return;

    while (n <= size)
        n = (n * 3) + 1;

    while (n > 1)
    {
        n = (n - 1) / 3;
        for (i = 0; i < size - n; i++)
        {
            for (j = i + n; j > 0 && j >= n; j -= n)
            {
                if (array[j] < array[j - n])
                {
                    temp = array[j - n];
                    array[j - n] = array[j];
                    array[j] = temp;
                }
            }
        }
        print_array(array, size);
    }
}

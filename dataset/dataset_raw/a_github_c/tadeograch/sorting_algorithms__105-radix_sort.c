#include <stdio.h>
#include "sort.h"


void radix_sort(int *array, size_t size)
{
    int digits = 0, i, j, max_num = 0, start = 0, len, at_index = 0, div = 10, temp, a;
    int *arr_aux;
    int *arr_aux2;

    len = (int)size;
    arr_aux = malloc(sizeof(int) * size);
    arr_aux2 = malloc(sizeof(int) * size);
    arr_cpy(array, arr_aux2, len);
    for(i = 0; i < len; i++)
    {
        if(array[i] > max_num)
            max_num = array[i];
    }
    while(max_num > 0)
    {
        max_num = max_num / 10;
        digits++;
    }

    while(digits >= 0)
    {
        for(a = 0; a < len; a++)
        {
            if(arr_aux2[a] != 0)
                arr_aux[a] = arr_aux2[a] % 10;
            else
                arr_aux[a] = arr_aux2[a];
        }
        print_array(arr_aux, size);
        for(start = 0; start < len; start++)
        {
            at_index = get_index_lower(arr_aux, start, len);
            printf("index: %d\n", at_index);
            temp = array[start];
            array[start] = array[at_index];
            array[at_index] = temp;
        }
        print_array(arr_aux2, size);
        for(j = 1; j < len; j++)
        {
            arr_aux2[i] = arr_aux2[i] / div; 
        }
        div = div * 10;
        
        digits--;
    }
}



void arr_cpy(int *array1, int *array2, int size)
{
    int i;

    for(i = 0; i < size; i++)
    {
        array2[i] = array1[i];
    }
}

int get_index_lower(int *array, int start, int size)
{
    int min = 0, index = 0, i = start;

    for(i = 0; i < size; i++)
    {
        if (array[i] < min)
            min = array[i];
            index = i;
    }
    return(index);
}
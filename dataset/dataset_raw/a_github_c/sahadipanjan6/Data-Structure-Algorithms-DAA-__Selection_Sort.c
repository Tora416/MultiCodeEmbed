#include<stdio.h>
#define MAX 10


void display(int array[MAX], int length);
void selection_sort(int array[MAX], int length);

void main()
{
    int i = 0;
    int size = 0;
    
    printf("\nEnter number of elements: \n");
    scanf("%d", &size);
    int input_array[size];

    printf("\nEnter the array elements...\n");
    for(i=0; i<size; i++)
        scanf("%d", &input_array[i]);

    
    printf("\nOriginal Array is as follows:- \n");
    display(input_array, size);

    
    selection_sort(input_array, size);

    
    printf("\nAfter Selection Sorting:- \n");
    display(input_array, size);
    printf("\n");
}


void display(int array[MAX], int length)
{
    int i = 0;
    for(i=0; i<length; i++)
        printf("%d\t", array[i]);

    printf("\n");
}


void selection_sort(int array[MAX], int length)
{
    int i, j, temp, pointer = 0;
    int size = length;

    for(i=0; i<size-1; i++)
    {
        
        pointer = i;
        for(j=i+1; j<size; j++)
        {
            
            if(array[pointer] > array[j])
            {
                
                pointer = j;
            }

            if(pointer != i)
            {
                
                temp = array[pointer];
                array[pointer] = array[i];
                array[i] = temp;
            }
        }
    }
}
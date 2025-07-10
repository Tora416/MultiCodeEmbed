#include<stdio.h>
#define MAX 10


void display(int array[MAX], int length);
void insertion_sort(int array[MAX], int length);

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

    
    insertion_sort(input_array, size);

    
    printf("\nAfter Insertion Sorting:- \n");
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


void insertion_sort(int array[MAX], int length)
{
    int i, j, temp = 0;
    int size = length;

    for(i=1; i<size; i++)
    {
        j = i;
        while((array[j] < array[j-1]) && j>0)
        {
            
            temp = array[j];
            array[j] = array[j-1];
            array[j-1] = temp;
            j--;
        }
    }
}
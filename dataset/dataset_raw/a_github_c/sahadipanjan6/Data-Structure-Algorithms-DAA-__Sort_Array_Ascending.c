#include<stdio.h>
#define MAX 10


void display(int array[MAX], int length);
void sorting(int array[MAX], int length);


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

    
    printf("\nArray after Sorting is as follows:- \n");
    sorting(input_array, size);
}


void display(int array[MAX], int length)
{
    int i = 0;
    for(i=0; i<length; i++)
        printf("%d\t", array[i]);
}


void sorting(int array[MAX], int length)
{
    int i, j, temp = 0;
    int size = length;
    
    for(i=0; i<length; i++)
    {
        for(j=i+1; j<length; j++)
        {
            
            if(array[i] > array[j])
            {
                temp = array[i];
                array[i] = array[j];
                array[j] = temp;
            }
        }
    }

    
    display(array, size);
}
#include<stdio.h>
#define MAX 10


void display(int array[MAX], int length);
int linear_search(int array[MAX], int length, int key);

void main()
{
    int i, size, key = 0;
        
    printf("\nEnter number of elements: \n");
    scanf("%d", &size);
    int input_array[size];

    printf("\nEnter the array elements...\n");
    for(i=0; i<size; i++)
        scanf("%d", &input_array[i]);

    
    printf("\nOriginal Array is as follows:- \n");
    display(input_array, size);

    
    printf("\nEnter the key to be searched: \n");
    scanf("%d", &key);

    
    printf("\n%d is found in Index %d\n", key, linear_search(input_array, size, key));
}


void display(int array[MAX], int length)
{
    int i = 0;
    for(i=0; i<length; i++)
        printf("%d\t", array[i]);

    printf("\n");
}


int linear_search(int array[MAX], int length, int key)
{
    int i, index = -1;
    int size = length;

    for(i=0; i<size; i++)
    {
        
        if(array[i] == key)
        {
            index = i;
            break;
        }
        else
            continue;
    }

    return index;
}
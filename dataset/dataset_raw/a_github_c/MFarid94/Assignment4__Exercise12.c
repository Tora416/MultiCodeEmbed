

#include <stdio.h>

#define ARRAY_SIZE 15

int OddRepetitionNumberInArray(int *arr,int arr_size)
{
    int i,j;
    int count = 0;
    int index = 0;
    for(i=0;i<arr_size;i++)
    {
        for(j = 0; j < arr_size;j++)
        {
            
            if(arr[i] == arr[j])
            {
                index = i;
                count++;
            }
        }
        
        if(count%2 != 0)
        {
            break;
        }
        
        count = 0;
    }
    return arr[index];
}

int main(void)
{
    int arr[ARRAY_SIZE] = {1,2,3,1,2,3,1,1,1,1,3,3,3};

    int num = OddRepetitionNumberInArray(arr,ARRAY_SIZE);

    printf("number is : %d",num); 

    return 0;
}

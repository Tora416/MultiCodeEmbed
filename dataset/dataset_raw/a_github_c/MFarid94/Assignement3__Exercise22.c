

#include <stdio.h>

#define ERROR 0
#define SUCCESS 1


int removeDuplicates(int arr_old[], int n_old, int arr_new[], int *n_new)
{
    int i=0;

    
    if (n_old==0)
        return ERROR;

    for (i=0 ; i<n_old-1 ; i++)
    {
        
        if (arr_old[i] != arr_old[i+1])
        {
            arr_new[*n_new] = arr_old[i];
            (*n_new)++;
        }

    }

    
    arr_new[*n_new] = arr_old[i];
    (*n_new)++;

    return SUCCESS;
}

int main(void)
{
    int arr1[10] = {1,2,3,3,3,4,4,5,5,5};
    int arr2[10];
    int arr2_usedSize = 0;
    int ret,i;

    
    ret = removeDuplicates(arr1,10,arr2,&arr2_usedSize);

    if(ret == SUCCESS)
    {
        for(i=0;i<arr2_usedSize;i++)
        {
            printf("%d \t",arr2[i]);
        }
    }
}

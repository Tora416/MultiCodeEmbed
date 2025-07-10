

#include <stdio.h>


int OutputArray[256];

int * PrintReverseInclusive(int LowerNumber,int UpperNumber,int * result_size)
{
    int i;
    *result_size = 0;
    
    if((LowerNumber>=UpperNumber) || (UpperNumber-1 == LowerNumber))
    {
        OutputArray[0] = 0xFF;
        OutputArray[1] = 0xFF;
        *result_size = 2;
    }
    else
    {
        
        for(i=UpperNumber-1;i>LowerNumber;i--)
        {
            OutputArray[*result_size] = i;
            (*result_size)++;
        }
    }
    return OutputArray;
}

int main(void) {
    int count;
    int n1 = 5,n2=10;
    int *ptr;
    int arr_size_used = 0;

    ptr = PrintReverseInclusive(n1,n2,&arr_size_used);

    printf("Output Array = ");

    
    for(count=0;count<arr_size_used;count++)
    {
        
        printf("%d ",ptr[count]);
    }
    printf("\nOutput Array Size = %d",arr_size_used);
    return 0;
}

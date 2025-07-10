



#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
    int num;
    int count_sevens = 0;
    int units;

    printf("Enter A Number : ");
    scanf("%d" , &num);

    while(num != 0)
    {
        units = abs(num % 10);                                          
        if(units == 7)                                                  
            count_sevens++;                                             

        num /= 10;                                                      
    }

    printf("\nNumber Of Sevens = %d\n" , count_sevens);

    return 0;
}

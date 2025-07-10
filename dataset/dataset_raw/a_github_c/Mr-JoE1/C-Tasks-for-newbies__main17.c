



#include <stdio.h>
#include <stdlib.h>



int BinaryToDecimal( int binary );

int main()
{
    int binary;

    printf("Enter Number In Binary Form : ");
    scanf("%d" , &binary);

    printf("\nNumber = %d\n" , BinaryToDecimal( binary ) );

    return 0;
}


int BinaryToDecimal( int binary )
{
    int PowerOfTwo = 1;
    int decimal = 0;

    while(binary != 0)
    {
        decimal += (binary % 10) * PowerOfTwo;                  
        binary /= 10;
        PowerOfTwo = PowerOfTwo << 1;                           
    }
    return decimal;
}

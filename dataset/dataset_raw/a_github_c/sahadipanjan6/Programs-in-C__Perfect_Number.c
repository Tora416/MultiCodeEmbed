#include<stdio.h>


int isPerfect(int number);

void main()
{
    int number = 0;

    printf("\nEnter any number: ");
    scanf("%d", &number);

    if(isPerfect(number) == 1)
        printf("%d is a Perfect Number\n", number);

    else
        printf("%d is NOT a Perfect Number\n", number);
}


int isPerfect(int number)
{
    int i = 0;
    int sum_factors = 0;

    for(i=1; i<number; i++)
    {
        if(number%i == 0)
            sum_factors += i;
    }

    if(sum_factors == number)
        return 1;

    return 0;
}
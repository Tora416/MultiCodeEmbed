#include <stdio.h>

int main()
{
    int sum1 = 0;
    int sum2 = 0;
    int sum3 = 0;
    int i = 1;
    int j = 1;

    printf("Petla for:\n");
    for (int i = 1; i <=100; i +=2)
    {
        sum1 += i;
        printf ("%d\n", sum1 );
    }

    printf("\nPetla while:\n");
    while (i <= 100)
    {
        sum2 += i;
        printf("%d\n", sum2);
        i += 2;
    }

    printf("\nPetla do while:\n");
    do {
        sum3 += j;
        printf("%d\n", sum3);
        j += 2;
    } while (j <= 100);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>

int change(int * x, int * y);

int main()
{
    int number1, number2;

    printf("Podaj liczbe calkowita nr 1: ");
    scanf("%d", &number1);
    printf("Podaj liczbe calkowita nr 2: ");
    scanf("%d", &number2);

    printf("\nLiczba1: %d     Liczba2: %d\n\n", number1, number2);
    change(&number1, &number2);
    printf("Liczba1: %d     Liczba2: %d\n\n", number1, number2);

    getchar();
    return 0;
}

int change(int * x, int * y){
    if(*y < *x){
        int temp = *x;
        *x = *y;
        *y = temp;
    }
    return 0;
}

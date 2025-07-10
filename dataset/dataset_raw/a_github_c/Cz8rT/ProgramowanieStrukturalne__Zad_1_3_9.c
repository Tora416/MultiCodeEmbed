#include <stdio.h>
#include <stdlib.h>

int main()
{
    float num1, num2;
    int operation;
    float result;

    printf("Podaj wartosc pierwszej liczby.\n");
    scanf("%f", &num1);
    printf("Podaj wartosc drugiej liczby.\n");
    scanf("%f", &num2);

    printf("Wybierz rodzaj operacji matematycznej.\n");
    printf("---------------------------------------\n");
    printf("1) Dodaj                   3) Pomnoz\n");
    printf("2) Odejmij                 4) Podziel\n");
    scanf("%d", &operation);

    switch (operation) {
    case 1:
        result = num1 + num2;
        break;
    case 2:
        result = num1 - num2;
        break;
    case 3:
        result = num1 * num2;
        break;
    case 4:
        result = num1 / num2;
        break;
    }

    printf("\nWynik: %.2f\n", result);

    getchar();
    return 0;
}

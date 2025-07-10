#include <stdio.h>
#include <stdlib.h>
#define BASICHOUR 40
#define OVERTIME 1.5
#define TAX1 0.15
#define TAX2 0.20
#define TAX3 0.25

int main()
{
    int workHours;
    float brutto;
    float podatek;

    printf("Podaj liczb\251 przepracowanych godzin w tygodniu: ");
    scanf("%d", &workHours);

    if(workHours >= 40) {
        brutto = 40 * BASICHOUR + (workHours - 40) * BASICHOUR * OVERTIME;
    } else {
        brutto = workHours * BASICHOUR;
    }

    if (brutto <= 1200) {
        podatek = brutto * TAX1;
    } else if (brutto > 1200 && brutto <= 1800) {
        podatek = 1200 * TAX1 + (brutto - 1200) * TAX2;
    } else {
        podatek = 1200 * TAX1 + (600) * TAX2 + (brutto - 1800) * TAX3;
    }

    printf("\nWynagrodzenie brutto: %.2fz\210\n", brutto);
    printf("Podatek: %.2fz\210\n", podatek);
    printf("Wynagrodzenie netto: %.2fz\210\n", brutto - podatek);

    getchar();
    return 0;
}


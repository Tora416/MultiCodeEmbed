#include <stdio.h>
#include <stdlib.h>

int kwadrat(int);
int szescian(int);

int main()
{
    int userMin, userMax;

    printf("Podaj liczb\251 dolnej granicy tabeli: ");
    scanf("%d", &userMin);
    printf("Podaj liczb\251 g\242rnej granicy tabeli: ");
    scanf("%d", &userMax);

    printf("\nLiczba\t\tKwadrat\t\tSze\230cian");

    for(char i = userMin; i <= userMax; i++) {
        printf("\n%5d\t\t%5d\t\t%5d", i, kwadrat(i), szescian(i));
    }

    getchar();
    return 0;
}

int kwadrat(int x) {
    return x*x;
}

int szescian(int x) {
    return x*x*x;
}


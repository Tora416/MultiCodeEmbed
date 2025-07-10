#include <stdio.h>
#include <stdlib.h>

int main()
{
    float a, b, c;
    float delta;
    float x1, x2;

    printf("Podaj wartosc wspolczynnika a.\n");
    scanf("%f", &a);
    printf("Podaj wartosc wspolczynnika b.\n");
    scanf("%f", &b);
    printf("Podaj wartosc wspolczynnika c.\n");
    scanf("%f", &c);

    if (a == 0) {
        x1 = -c/b;
        printf("Rozwiazanie rownania: %.2f\n", x1);
    } else {
        delta = b*b-4*a*c;
        if (delta < 0) {
           printf("Rownanie nie ma rozwiazan w zbiorze liczb rzeczywistych.\n");
        } else {
            x1 = (-b-delta)/(2*a);
            x2 = (-b+delta)/(2*a);
            printf("x1 wynosi: %.2f\n", x1);
            printf("x2 wynosi: %.2f\n", x2);
        }
    }

    getchar();
    return 0;
}

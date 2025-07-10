#include <stdio.h>
#include <stdlib.h>

int main()
{
    float a, b, c;
    int licznik = 0;

    printf("Podaj 1 liczbe: ");
    scanf("%f", &a);
    printf("Podaj 2 liczbe: ");
    scanf("%f", &b);
    printf("Podaj 3 liczbe: ");
    scanf("%f", &c);

    if(a >= b && a >= c ) {
        printf("Najwieksza liczba to %.2f\n", a);
        if(b >= c) {
            printf("Najmniejsza liczba to %.2f\n", c);
        } else {
            printf("Najmniejsza liczba to %.2f\n", b);
        }
    } else if ( b >= c) {
        printf("Najwieksza liczba to %.2f\n", b);
        if(a >= c) {
            printf("Najmniejsza liczba to %.2f\n", c);
        } else {
            printf("Najmniejsza liczba to %.2f\n", a);
        }
    } else {
        printf("Najwieksza liczba to %.2f\n", c);
        if(a >= b) {
            printf("Najmniejsza liczba to %.2f\n", b);
        } else {
            printf("Najmniejsza liczba to %.2f\n", a);
        }
    }

    printf("\n");
    return 0;
}

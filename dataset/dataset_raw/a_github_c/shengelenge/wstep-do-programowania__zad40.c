#include <stdio.h>
#include <math.h>

int main()
{
    double a, b, c;
    double x1, x2;
    double delta;

    printf("Podaj liczby a, b i c:\n");
    printf("a = ");
    scanf("%lf", &a);
    printf("b = ");
    scanf("%lf", &b);
    printf("c = ");
    scanf("%lf", &c);

    delta = b*b - 4*a*c;

    if (delta > 0)
    {
        x1 = (-1*b +  sqrt(delta))/2*a;
        x2 = (-1*b -  sqrt(delta))/2*a;
        printf("Miejsca zerowe funkcji f(x) = %.1lf x^2 + %.1lf x + %.1lf , x1 = %.1lf , x2 = %.1lf", a,  b, c, x1, x2);
    }

    if (delta == 0)
    {
        x1 = (-1*b)/2*a;
        printf("Miejsce zerowe funkcji f(x) = %.1lf x^2 + %.1lf x + %.1lf , x = %.1lf", a,  b, c, x1);
    }

    if (delta < 0)
        printf("Brak miejsc zerowych.");

    return 0;
}
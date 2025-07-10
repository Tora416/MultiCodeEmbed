#include <stdio.h>
#include <math.h>

double E = 0.000001;

double pierwiastek(double p, double E)
{
    double a = 1, b = p;

    while (fabs(a - b) >= E)
    {
        a = (a + b) / 2;
        b = p / a;
    }

    return a;
}

int main()
{
    double x, y;

    printf("Podaj liczbe, z ktorej chcesz wyznaczyc pierwiastek: ");
    scanf("%2lf", &x);

    y = pierwiastek(x, E);

    printf("Pierwiastek = %.3lf", y);

    return 0;
}
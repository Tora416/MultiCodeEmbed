#include <stdio.h>

int main()
{
    double a, b, c;

    printf("Podaj 3 liczby typu double:\n");
    scanf("%lf\n%lf\n%lf", &a, &b, &c);

    if (a > b && a > c)
    {
        if (b > c)
        {
            printf("%.2lf, %.2lf, %.2lf", c, b,a);
        } else
            printf("%.2lf, %.2lf, %.2lf", b, c, a);
    }

    if (b > a && b > c)
    {
        if (a > c)
        {
            printf("%.2lf, %.2lf, %.2lf", c, a, b);
        } else
            printf("%.2lf, %.2lf, %.2lf", a, c, b);
    }

    if (c > a && c > b)
    {
        if (a > b)
        {
            printf("%.2lf, %.2lf, %.2lf", b, a, c);
        } else
            printf("%.2lf, %.2lf, %.2lf", a, b, c);
    }

    return 0;
}
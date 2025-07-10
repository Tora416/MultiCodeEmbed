#include <stdio.h>
#include <math.h>

int main()
{
    float a, b, c, x1, x2, x, delta, real, im1, im2;

    printf("\nDe acordo com o modelo de equação: ax²+bx+c\n\n");
    printf("Informe 'a': ");
    scanf("%f", &a);
    printf("Informe 'b': ");
    scanf("%f", &b);
    printf("Informe 'c': ");
    scanf("%f", &c);

    delta = pow(b, 2) - 4 * a * c;

    if (delta == 0)
    {
        x = (-b) / (2 * a);

        printf("\nA equação tem raiz dupla\nx = %.2f\n\n", x);
    }

    else if (delta < 0)
    {
        delta = -delta;
        real = (-b) / (2 * a);
        im1 = sqrt(delta) / (2 * a);
        im2 = (-sqrt(delta)) / (2 * a);

        printf("\nA equação tem raiz imaginária\nParte real = %.2f\nParte imaginária = %.2fi e %.2fi\n\n", real, im1, im2);
    }

    else
    {
        x1 = (-b + sqrt(delta)) / (2 * a);
        x2 = (-b - sqrt(delta)) / (2 * a);

        printf("\nA equação tem raizes reais\nx1 = %.2f\nx2 = %.2f\n\n", x1, x2);
    }

    return 0;
}
#include <stdio.h>
#include <stdlib.h>

double exponencial(double a, int n)
{
    if (n == 0) return 1;

    else if (n == 1) return a;

    else if (n < 0) return exponencial(1/a, (-1)*n);

    else if (n % 2 == 0) return exponencial(a, n/2) * exponencial(a, n/2);

    else return exponencial(a, n-1) * exponencial(a, 1);
}

int main()
{
    double a;
    int n;

    printf("\nFunção exponencial (a^n):\n");
    printf("\t -> (real) a: ");
    scanf("%lf", &a);
    getchar();
    printf("\t -> (int) n: ");
    scanf("%i", &n);

    printf("\n%lf^%i = %lf\n\n", a, n, exponencial(a,n));

    return 0;
}
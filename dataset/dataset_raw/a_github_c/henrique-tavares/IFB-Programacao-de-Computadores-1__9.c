#include <stdio.h>
#include <stdlib.h>

double exponencial(int a, long long int n)
{
    if (n == 0) return 1;

    else if (n == 1) return a;

    else if (n % 2 == 0) return exponencial(a, n/2) * exponencial(a, n/2);

    else return exponencial(a, n-1) * exponencial(a, 1);
}

long long int fatorial(int n)
{
    return (n > 1) ? n * fatorial(n-1) : 1;
}

double super_fatorial(int n)
{
    return (n > 1) ? exponencial(n, fatorial(n-1)) : 1;
}

int main()
{
    int n;

    do
    {
        printf("\nDigite um inteiro positivo: ");
        scanf("%i", &n);
        getchar();
        system("clear");

    } while(n <= 0);

    if (n >= 5) printf("\nFatorial exponencial de %i = %e\n\n", n, super_fatorial(n));

    else printf("\nFatorial exponencial de %i = %.0lf\n\n", n, super_fatorial(n));

    return 0;
}
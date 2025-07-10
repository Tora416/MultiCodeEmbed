#include <stdio.h>
#include <math.h>
#include "funcoes.h"

double fatorial(int n)
{
    double x = 1;

    for (int i = 2; i <= n; i++)
    {
        x *= i; 
    }

    return x; 
}

double f_de_x(int n, double a[], double x) 
{
    double soma = 0;

    for (int i = 0; i <= n; i++)
    {
        soma += a[i] * pow(x, i); 
    }

    return soma; 
}

int f_de_x_taylor(int n, double at[], double x, double xf)
{
    double soma = 0;

    for (int i = 0; i <= n; i++)
    {
        soma += (at[i] * pow(x, i)) / fatorial(i); 

        printf("%i %lf %lf\n", i + 1, soma, xf); 

        if (fabs(soma - xf) <= 0.001) 
            return 0;
    }

    return 0;
}

void vetor_taylor(int n, double a[], double x, double xf)
{
    double at[7];

    for (int i = 0; i <= n; i++)
    {
        at[i] = a[i]; 
    }

    for (int i = 1; i <= n; i++)
    {
        for (int j = i; j > 0; j--)
        {
            at[i] *= j; 
        }
    }

    f_de_x_taylor(n, at, x, xf); 
}
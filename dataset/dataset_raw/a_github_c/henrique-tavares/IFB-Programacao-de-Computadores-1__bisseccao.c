#include <stdio.h>
#include <stdlib.h>
#include <math.h> 
#include "funcoes.h" 
#define iteracoes 10000

int main()
{
    int n;
    double a[7], l, r, m;

    scanf("%i", &n); 
    getchar();

    for (int i = 0; i <= n; i++)
    {
        scanf("%lf", &a[i]); 
        getchar();
    }

    scanf("%lf", &l); 
    getchar();
    scanf("%lf", &r); 
    getchar();

    for (long int i = 0; i <= iteracoes; i++)
    {

        m = l + ((r-l)/2);

        if (fabs(f_de_x(n, a, m)) <= 0.0001) 
        {
            printf("\n%lf\n\n", m); 
            return 0;
        }

        if ((f_de_x(n, a, m) * f_de_x(n, a, l)) < 0) 
        {
            r = m; 
        }
        
        else 
        {
            l = m; 
        }

        if (i == iteracoes)
        {
            printf("raiz nao encontrada\n"); 
        }

    }

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <math.h> 
#include "funcoes.h" 

int main()
{
    int n, q;
    double a[7], x[100], xf;

    scanf("%i", &n); 
    getchar();

    for (int i = 0; i <= n; i++)
    {
        scanf("%lf", &a[i]); 
        getchar();
    }

    scanf("%i", &q); 

    for (int i = 0; i < q; i++)
    {
        scanf("%lf", &x[i]); 
        getchar();
    }

    putchar('\n');
    for (int i = 0; i < q; i++)
    {
        xf = f_de_x(n, a, x[i]); 

        vetor_taylor(n, a, x[i], xf); 
        
        putchar('\n');
    }

    return 0;
}
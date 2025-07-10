#include <stdio.h>
#include <math.h>
#define true 1
#define false 0
#define iteracoes 30

double x,seno;
int i,j;

double fatorial (int i)
{
    double res = 1;
    for (int j=1; j<i; j++)
    {
        res = res*(j+1);
    }
    return res;
}

double potencia (double x, int i)
{
    double x0 = 1;
    for (int j=0; j<i; j++)
    {
        x0 *= x;
    }

    return x0;
}

int main()
{
    scanf ("%lf",&x);
    seno = x;

    for (int i=3,j=1; j<=iteracoes; i=i+2,j++)
    {
        if ((j%2) == 0)
        {
            seno += potencia(x,i)/fatorial(i);
        }
        else
        {
            seno -= potencia(x,i)/fatorial(i);
        }    
        
    }

    printf ("%.10lf\n", seno);
    return 0;
}
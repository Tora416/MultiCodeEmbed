#include <stdio.h>
#include <math.h>

int main()
{
    double x[1000], y[1000], d, menor;
    int n, p1, p2;

    scanf ("%i", &n);

    for (int i=0; i<n; i++)
    {
        scanf ("%lf", &x[i]);
    }
    
    for (int i=0; i<n; i++)
    {
        scanf ("%lf", &y[i]);
    }

    for (int i=0; i<n; i++)
    {
        for (int j=(i+1); j<n; j++)
        {
            d = pow((x[i]-x[j]),2) + pow((y[i]-y[j]),2);
            d = sqrt(d);
            
            if ((i==0)&&(j==1))
            {
                menor = d;
                p1 = i;
                p2 = j;
            }
            else
            {
                if (d < menor)
                {
                    menor = d;
                    p1 = i;
                    p2 = j;
                }
            }
            
        }
    }

    printf ("Pontos: %i e %i\nDistancia: %lf\n", p1, p2, menor);

    return 0;
}
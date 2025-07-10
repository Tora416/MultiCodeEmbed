#include <stdio.h>
#include <math.h>

void potencia(float x, int n, float xp[])
{
    float x0 = 1;
    xp[0] = 1;

    for (int i = 1; i <= n; i++)
    {
        x0 *= x;
        xp[i] = x0;
        
    }
}

int main()
{
    int n;
    long int q;
    float x[100000], av[6], soma = 0, xp[5];

    scanf("%i", &n);

    for (int i = 0; i <= n; i++)
    {
        scanf("%f", &av[i]);
    }

    scanf("%li", &q);

    for (int i = 0; i < q; i++)
    {
        scanf("%f", &x[i]);
    }

    for (int i = 0; i < q; i++)
    {
        potencia(x[i], n, xp);

        for (int j = 0; j <= n; j++)
        {
            soma += av[j] * xp[j];
            
        }

        printf("%f\n", soma);
        soma = 0;
    }

    return 0;
}
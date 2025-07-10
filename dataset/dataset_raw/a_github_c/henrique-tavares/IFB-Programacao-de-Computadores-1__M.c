#include <stdio.h>
#define true 1
#define false 0

int sistema(int a, int b, int c)
{
    int x, y, z;
    for (y = (-c); y <= c; y++)
    {
        for (z = (y+1); z <= c; z++)
        {
            x = a - y - z;
            if (((y * z * x) == b) && (((x * x) + (y * y) + (z * z)) == c) && (z != x) && (y != x))
            {
                printf("%i %i %i\n", y, z, x);
                return 0;
            }
        }
    }
    printf("Sem solucao\n");
    
    return 0;
}

int main()
{
    int n, av[10000], bv[10000], cv[10000], xv[100000], yv[100000], zv[100000], a, b, c, x, y, z, k = 0, solucao, solucao2, aux;

    scanf("%i", &n);

    for (int i = 0; i < n; i++)
    {
        scanf("%i", &av[i]);
        scanf("%i", &bv[i]);
        scanf("%i", &cv[i]);
    }

    for (int i = 0; i < n; i++)
    {
        sistema (av[i], bv[i], cv[i]);
    }
    return 0;
}
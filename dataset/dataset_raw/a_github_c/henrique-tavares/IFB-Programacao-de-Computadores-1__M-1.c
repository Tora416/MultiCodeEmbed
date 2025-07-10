#include <stdio.h>
#define true 1
#define false 0

int main()
{
    int n, av[10000], bv[10000], cv[10000], xyz[100000], a, b, c, x, y, z, k = 0, solucao, solucao2, aux;

    scanf("%i", &n);

    for (int i = 0; i < n; i++)
    {
        scanf("%i", &av[i]);
        scanf("%i", &bv[i]);
        scanf("%i", &cv[i]);
    }

    for (int i = 0; i < n; i++)
    {
        a = av[i];
        b = bv[i];
        c = cv[i];

        solucao2 = false;

        for (y = (-c); y <= c; y++)
        {
            for (z = y; z <= c; z++)
            {
                x = a - y - z;
                if (((y * z * x) == b) && (((x * x) + (y * y) + (z * z)) == c))
                {
                    solucao = true;
                    if (k != 0)
                    {
                        for (int j=0; j<=(k-3); j++)
                        {
                            if ((x == xyz[j])||(y == xyz[j])||(z == xyz[j]))
                            {
                                solucao = false;
                                break;
                            }
                        }
                    }
                    if (solucao == true)
                    {
                        printf("%i %i %i\n", y, z, x);
                        solucao2 = true;
                        xyz[k] = x;
                        xyz[k+1] = y;
                        xyz[k+2] = z;
                        k += 3;
                    }
                }
            }
        }
        if (solucao2 == false)
            printf("Sem solucao\n");
    }
    return 0;
}
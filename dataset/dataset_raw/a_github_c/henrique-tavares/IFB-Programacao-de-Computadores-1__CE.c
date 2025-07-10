#include <stdio.h>
#include <limits.h>

int main()
{
    int matriz[1000][1000], n, soma, maior = INT_MIN, k0;

    scanf("%i", &n);

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            scanf("%i", &matriz[i][j]);
        }
    }

    for (int k = (-n + 1); k < n; k++)
    {
        soma = 0;
        for (int i = 0, j; i < n; i++)
        {
            j = i + k;
            if (j >= 0 && j < n)
            {
                soma += matriz[i][j];
            }
        }

        if (soma > maior)
        {
            maior = soma;
            k0 = k;
        }
    }

    printf("%i %i\n", k0, maior);

    return 0;
}
#include <stdio.h>

int main()
{
    double A[100][100], B[100][100], soma = 0;
    int n, m, k, l;

    scanf("%i %i %i %i", &n, &m, &k, &l);

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            scanf("%lf", &A[i][j]);
        }
    }

    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < l; j++)
        {
            scanf("%lf", &B[i][j]);
        }
    }

    if (m != k)
    {
        printf("impossivel\n");
        return 0;
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < l; j++)
        {
            for (int a = 0; a < m; a++)
            {
                soma += A[i][a] * B[a][j];
            }
            printf("%.2lf ", soma);
            soma = 0;
        }
        putchar('\n');
    }

    return 0;
}
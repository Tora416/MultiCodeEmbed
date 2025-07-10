#include <stdio.h>

int main()
{
    float A[100][100];
    int n, m;

    scanf("%i %i", &n, &m);

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            scanf("%f", &A[i][j]);
        }
    }

    for (int j = 0; j < m; j++)
    {
        for (int i = 0; i < n; i++)
        {
            if (i == (n-1)) printf("%.2f", A[i][j]);
            
            else printf("%.2f ", A[i][j]);
        }
        putchar('\n');
    }

    return 0;
}
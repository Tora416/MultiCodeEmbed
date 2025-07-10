#include <stdio.h>
#define true 1
#define false 0

int popstar(int N[][1000], int j, int n)
{
    for (int i = 0; i < n; i++)
    {
        if (N[i][j] != 1) return false;
    }

    return true;
}

int main()
{
    int N[1000][1000], n, maybe[1000], busca, busca_p, k = 0;

    scanf("%i", &n);

    for (int i = 0; i < n; i++)
    {
        busca = true;

        for (int j = 0; j < n; j++)
        {
            scanf("%i", &N[i][j]);
            
            if ((j != i) && (N[i][j] != 0)) busca = false;
            else if ((j == i) && (N[i][j] != 1)) busca = false;
            
        }

        if (busca == true)
        {
            maybe[k] = i;
            k++;
        }
    }

    if (k == 0)
    {
        printf("Nao ha popstar.\n");
        return 0;
    }

    for (int i = 0; i < k; i++)
    {
        busca_p = popstar(N, maybe[i], n);

        if (busca_p == true) printf("Popstar: aluno #%i\n", maybe[i] + 1);
    }

    return 0;
}
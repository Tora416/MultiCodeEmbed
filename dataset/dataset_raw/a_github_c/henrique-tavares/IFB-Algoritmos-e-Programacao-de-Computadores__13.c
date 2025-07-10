#include <stdio.h>
#include <stdlib.h>

int main()
{
    int matriz[4][4];
    int soma = 0;
    system("clear");
    printf("Informe os elementos(int) de uma matriz 4x4:\n");

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            scanf("%i", &matriz[i][j]);
            if (i == j)
            {
                soma += matriz[i][j];
            }
        }
    }

    system("clear");
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (j == 0)
            {
                printf("|");
            }
            printf("%3i", matriz[i][j]);
            if (j == 3)
            {
                printf(" |");
            }
        }
        printf("\n");
    }
    printf("\nA soma dos elementos da diagonal principal é: %d\n\n", soma);
    return 0;
}
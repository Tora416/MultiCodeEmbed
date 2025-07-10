#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    char nomes1[4][10], nomes2[4][10], quadrilha[4][2][10];

    system("clear");
    printf("Informe os primeiros 4 nomes (sem acentuação):\n");
    for (int i = 0; i < 4; i++)
    {
        scanf("%10[^\n]s", nomes1[i]);
        getchar();
    }
    printf("\nInforme os últimos 4 nomes (sem acentuação):\n");
    for (int i = 0; i < 4; i++)
    {
        scanf("%10[^\n]s", nomes2[i]);
        getchar();
    }

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            if (j == 0)
            {
                strcpy(quadrilha[i][j], nomes1[i]);
            }
            else if (j == 1)
            {
                strcpy(quadrilha[i][j], nomes2[i]);
            }
        }
    }

    system("clear");
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            if (j == 0)
            {
                printf("|");
            }
            printf(" %-10s ", quadrilha[i][j]);
            if (j == 1)
            {
                printf("|");
            }
        }
        printf("\n");
    }
    printf("\n\n");
    return 0;
}
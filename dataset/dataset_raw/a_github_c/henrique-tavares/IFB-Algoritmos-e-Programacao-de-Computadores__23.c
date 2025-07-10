#include <stdio.h>
#include <stdlib.h>

int main()
{
    char matriz[3][5];

    system("clear");

    printf("informe os elementos(char) de uma matriz 3x5:\n");
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            scanf("%c", &matriz[i][j]);
            getchar();
        }
    }

    system("clear");

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (j == 0)
            {
                printf("|");
            }
            printf("%2c", matriz[i][j]);
            if (j == 4)
            {
                printf(" |");
            }
        }
        printf("\n");
    }
    printf("\n");

    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (j == 0)
            {
                printf("|");
            }
            printf("%2c", matriz[j][i]);
            if (j == 2)
            {
                printf(" |");
            }
        }
        printf("\n");
    }
    printf("\n");
    return 0;
}
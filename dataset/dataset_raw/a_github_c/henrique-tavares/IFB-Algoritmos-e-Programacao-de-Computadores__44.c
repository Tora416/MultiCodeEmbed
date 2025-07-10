#include <stdio.h>

int main()
{
    int matriz[4][4];

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            scanf("%i", &matriz[i][j]);
        }
    }

    printf("\n");
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (j > i)
            {
                printf(" 0 ");
            }
            else
            {
                printf("%2i ", matriz[i][j]);
            }
        }
        printf("\n");
    }
    printf("\n\n");
    return 0;
}
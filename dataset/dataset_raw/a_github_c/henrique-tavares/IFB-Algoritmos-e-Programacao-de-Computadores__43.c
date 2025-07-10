#include <stdio.h>
#include <stdlib.h>

int main()
{
    int restaurante[8][4];
    int cadeira = 1;

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            switch (j)
            {
            case 0:
                restaurante[i][j] = cadeira;
                break;
            case 1:
                restaurante[i][j] = cadeira + 1;
                break;
            case 2:
                restaurante[i][j] = cadeira + 4;
                break;
            case 3:
                restaurante[i][j] = cadeira + 5;
                break;
            }
        }
        if ((i % 2) == 0)
        {
            cadeira += 2;
        }
        else
        {
            cadeira += 6;
        }
    }

    system("clear");
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            printf("%3i", restaurante[i][j]);
        }
        printf("\n");
    }

    printf("\n");
    return 0;
}
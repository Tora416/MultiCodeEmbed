#include <stdio.h>
#define mlinhas 9
#define ncolunas 9

int main()
{
    int linha = 1, coluna = 1;
    char a = 'a';
    printf("\n");

    for (int m = 0; m < mlinhas; m++)
    {
        for (int n = 0; n < ncolunas; n++)
        {
            if (coluna == 1)
            {
                printf("| ");
            }
            printf("%c%i%i  ", a, linha, coluna);
            if (coluna == ncolunas)
            {
                printf("|");
            }
            coluna++;
        }
        printf("\n");
        linha++, coluna = 1;
    }
    printf("\n");
}

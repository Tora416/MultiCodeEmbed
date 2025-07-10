#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define true 1
#define false 0

int main()
{
    char str[1001];
    int num[1001], aux, aux0, qtd = 1;

    fgets(str, 1001, stdin);

    for (int i = 0; str[i] != '\0'; i++)
    {
        if (str[i] == '\n')
        {
            str[i] = '\0';
        }
    }

    for (int i = 0; str[i] != '\0';)
    {
        aux = atoi(&str[i]);
        aux0 = aux;
        

        while (aux0 >= 10)
        {
            aux0 /= 10;
            qtd++;
        }

        if ((aux != 0) && (str[i + qtd] != '\0'))
        {
            for (int j = 0; j < (aux - 1); j++)
            {
                printf("%c", str[i + qtd]);
            }
        }

        else
        {
            printf("%c", str[i]);
        }

        i += qtd;
        qtd = 1;
    }

    putchar('\n');
    return 0;
}
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main()
{
    char frase[50], esarf[50];
    int tam_frase, i = 0, i1, j = 0, k = 0;

    printf("\nInforme uma frase quanlquer:\n");
    scanf("%[^\n]s", frase);

    tam_frase = strlen(frase);
    i1 = tam_frase - 1;

    strcpy(esarf, frase);
    for (int i = 0; i < tam_frase; i++)
    {
        esarf[i] = frase[(tam_frase - 1) - i];
    }

    while (j != (tam_frase + 1))
    {
        while ((j <= tam_frase) && (frase[j] != ' '))
        {
            j++;
        }

        for (int j1 = j; j1 < tam_frase; j1++)
        {
            frase[j1] = frase[j1 + 1];
        }
    }

    while (k != (tam_frase + 1))
    {
        while ((k <= tam_frase) && (esarf[k] != ' '))
        {
            k++;
        }

        for (int k1 = k; k1 < tam_frase; k1++)
        {
            esarf[k1] = esarf[k1 + 1];
        }
    }

    for (int m = 0; frase[m]; m++)
    {
        frase[m] = tolower(frase[m]);
    }
    for (int n = 0; esarf[n]; n++)
    {
        esarf[n] = tolower(esarf[n]);
    }

    if (strcmp(frase, esarf) == 0)
    {
        printf("\nA Frase é um palíndromo.\n\n");
    }
    else
    {
        printf("\nA Frase não é um palíndromo.\n\n");
    }

    return 0;
}
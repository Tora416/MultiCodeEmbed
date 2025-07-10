#include <stdio.h>
#define tamanho 10

int main(void)
{
    int vetor[tamanho], aux, i = 0, k = 0, maior, menor, indice_maior[tamanho], indice_menor[tamanho];
    printf("\nInforme os números do vetor:\n");
    for (int a = 0; a < tamanho; a++)
    {
        scanf("%i", &vetor[a]);
        if (a == 0)
        {
            maior = vetor[a];
            indice_maior[i] = a;
            menor = vetor[a];
            indice_menor[k] = a;
        }
        else
        {
            if (vetor[a] > maior)
            {
                maior = vetor[a];
                for (int j = 0; j < tamanho; j++)
                {
                    indice_maior[j] = 0;
                }
                i = 0;
                indice_maior[i] = a;
            }
            else if (vetor[a] == maior)
            {
                i++;
                indice_maior[i] = a;
            }
            else if (vetor[a] < menor)
            {
                menor = vetor[a];
                for (int l = 0; l < tamanho; l++)
                {
                    indice_menor[l] = 0;
                }
                k = 0;
                indice_menor[k] = a;
            }
            else if (vetor[a] == menor)
            {
                k++;
                indice_menor[k] = a;
            }
        }
    }

    if (k != 0)
    {
        printf("\nMenor = indices ");
        for (int c = 0; c <= k; c++)
        {
            if (c == k)
            {
                printf("%i. ", indice_menor[c]);
            }
            else
            {
                printf("%i, ", indice_menor[c]);
            }
        }
        printf("com valor %i", menor);
    }
    else if (k == 0)
    {
        printf("\nMenor = indice %i com valor %i", indice_menor[k], menor);
    }

    if (i != 0)
    {
        printf("\nMaior = indices ");
        for (int b = 0; b <= i; b++)
        {
            if (b == i)
            {
                printf("%i. ", indice_maior[b]);
            }
            else
            {
                printf("%i, ", indice_maior[b]);
            }
        }
        printf("com valor %i", maior);
    }
    else if (i == 0)
    {
        printf("\nMaior = indice %i com valor %i", indice_maior[i], maior);
    }

    printf("\n\n");
    return 0;
}
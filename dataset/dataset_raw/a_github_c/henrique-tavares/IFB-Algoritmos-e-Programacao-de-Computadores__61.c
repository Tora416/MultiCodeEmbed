#include <stdio.h>
#define tamanho 20
#define true 1
#define false 0

int main(void)
{
    int vetor[tamanho], aux, pivo, n, busca = false;

    printf("\nInforme os números do vetor:\n");
    for (int i = 0; i < tamanho; i++)
    {
        scanf("%i", &vetor[i]);
        for (int j = i; j > 0; j--)
        {
            if (vetor[j] < vetor[j - 1])
            {
                aux = vetor[j];
                vetor[j] = vetor[j - 1];
                vetor[j - 1] = aux;
            }
        }
    }

    printf("\nVetor: ");
    for (int i = 0; i < tamanho; i++)
    {
        printf("%i ", vetor[i]);
    }

    pivo = tamanho / 2;

    printf("\nInforme qual número deseja buscar no vetor: ");
    scanf("%i", &n);

    for (int i = 0; i < (tamanho / 2); i++)
    {
        if (n == vetor[pivo])
        {
            busca = true;
        }
        else if (n < vetor[pivo - 1])
        {
            if ((pivo % 2) == 0)
            {
                pivo = pivo / 2;
            }
            else
            {
                pivo = (pivo + 1) / 2;
            }
        }
        else if (n > vetor[pivo - 1])
        {
            if ((pivo % 2) == 0)
            {
                pivo = pivo + (pivo / 2);
            }
            else
            {
                pivo = pivo + ((pivo + 1) / 2);
            }
        }
        else if (n == vetor[pivo - 1])
        {
            busca = true;
        }
    }

    if (busca == true)
    {
        printf("\nO número está no vetor\n");
    }
    else
    {
        printf("\nO número não está no vetor\n");
    }

    printf("\n\n");
    return 0;
}
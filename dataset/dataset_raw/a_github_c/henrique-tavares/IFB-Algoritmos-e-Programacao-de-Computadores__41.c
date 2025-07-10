#include <stdio.h>
#define tamanho 32

int main()
{
    int vetor[tamanho];
    int qtd1 = 0, qtd0, i, j;

    printf("\nInforme os números do vetor:\n");
    for (i = 0; i < tamanho; i++)
    {
        scanf("%i", &vetor[i]);
    }

    for (i = 0; i < tamanho; i++)
    {
        if (vetor[i] != 0)
        {
            vetor[i] = 1;
            qtd1++;
        }
    }

    qtd0 = tamanho - qtd1;

    printf("\nVetor: ");
    for (j = 0; j < tamanho; j++)
    {
        printf("%i ", vetor[j]);
    }

    printf("\nQuantidade de zeros: %i\nQuantidade de uns: %i\n\n", qtd0, qtd1);
    return 0;
}
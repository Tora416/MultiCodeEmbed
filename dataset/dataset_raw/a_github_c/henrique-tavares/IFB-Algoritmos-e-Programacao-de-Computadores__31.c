#include <stdio.h>
#define tamanho 5

int main(void)
{
    int a[tamanho], b[tamanho], aux;

    printf("\nInforme os números do vetor A:\n");
    for (int i = 0; i < tamanho; i++)
    {
        scanf("%i", &a[i]);
    }

    printf("\nInforme os números do vetor B:\n");
    for (int i = 0; i < tamanho; i++)
    {
        scanf("%i", &b[i]);
    }

    for (int j = 0; j < tamanho; j++)
    {
        aux = a[j];
        a[j] = b[j];
        b[j] = aux;
    }

    printf("\nVetor A: ");
    for (int k = 0; k < tamanho; k++)
    {
        printf("%i ", a[k]);
    }

    printf("\nVetor B: ");
    for (int k = 0; k < tamanho; k++)
    {
        printf("%i ", b[k]);
    }

    printf("\n\n");
    return 0;
}

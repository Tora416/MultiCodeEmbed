#include <stdio.h>
#define tamanho 10

int main(void)
{
    float vetor[tamanho], aux;
    int j = tamanho - 1;

    printf("Informe os números do vetor:\n");
    for (int i = 0; i < tamanho; i++)
    {
        scanf("%f", &vetor[i]);
    }

    for (int i = 0; i < (tamanho / 2); i++)
    {
        aux = vetor[i];
        vetor[i] = vetor[j];
        vetor[j] = aux;
        j--;
    }

    printf("\nVetor: ");
    for (int i = 0; i < tamanho; i++)
    {
        printf("%.2f ", vetor[i]);
    }

    printf("\n\n");
    return 0;
}
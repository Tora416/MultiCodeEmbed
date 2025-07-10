#include <stdio.h>
#include <stdlib.h>

typedef enum Ordem
{
    normal,
    inversa

} ordem_t;

void imprime_elemento(long int *vet, long int i, long int n, ordem_t ordem)
{
    printf("%li ", *(vet + i));

    if (ordem == normal)
    {
        return (i < n-1) ? imprime_elemento(vet, i+1, n, ordem) : 0;
    }
    
    else if (ordem == inversa)
    {
        return (i > 0) ? imprime_elemento(vet, i-1, NULL, ordem) : 0;
    }
}


int main()
{
    long int n, *vet;

    do
    {
        printf("\nDigite o tamanho do vetor: ");
        scanf("%ld", &n);
        getchar();
        system("clear");

    } while (n <= 0);

    vet = malloc(n * sizeof(long int));

    printf("\nDigite os elementos do vetor:\n");

    for (long int i = 0; i < n; i++)
    {
        printf("\t-> ");
        scanf("%ld", vet + i);
        getchar();
    }

    printf("\nOrdem normal:\n");
    printf("\t[ ");
    imprime_elemento(vet, 0, n, normal);
    printf("]\n");
    
    printf("\nOrdem inversa:\n");
    printf("\t[ ");
    imprime_elemento(vet, n-1, NULL, inversa);
    printf("]\n\n");

    return 0;
}
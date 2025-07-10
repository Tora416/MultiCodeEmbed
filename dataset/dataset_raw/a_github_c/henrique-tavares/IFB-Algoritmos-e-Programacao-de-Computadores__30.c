#include <stdio.h>

int main()
{
    int n, i, j, multiplo = 0;

    printf("\nInforme os números inteiros positivos 'n','i' e 'j'.\nOnde 'n' será a quantidade de números em ordem crescentes,\nque sejam múltiplos de 'i' ou de 'j' ou de ambos.\n");
    printf("\nInforme 'n': ");
    scanf("%i", &n);
    printf("\nInforme 'i': ");
    scanf("%i", &i);
    printf("\nInforme 'j': ");
    scanf("%i", &j);
    printf("\n");

    for (int qtd = 0; qtd < n;)
    {
        if (((multiplo % i) == 0) || ((multiplo % j) == 0))
        {
            if (qtd == (n - 1))
            {
                printf("%i.", multiplo);
            }

            else
            {
                printf("%i,", multiplo);
            }

            qtd++;
        }

        multiplo++;
    }

    printf("\n\n");
    return 0;
}
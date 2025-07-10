#include <stdio.h>

int main()
{
    int n, qtd = 2, idade, maior, menor;

    printf("\nInforme a quantidade de idades: ");
    scanf("%i", &n);

    printf("\nInforme a 1ª idade: ");
    scanf("%i", &idade);

    maior = idade;
    menor = idade;

    for (int i = 0; i < (n - 1); i++)
    {
        printf("\nInforme a %iª idade: ", qtd);
        scanf("%i", &idade);
        qtd++;

        if (idade > maior)
        {
            maior = idade;
        }

        else if (idade < menor)
        {
            menor = idade;
        }
    }

    printf("\nMaior idade: %i", maior);
    printf("\nMenor idade: %i\n\n", menor);

    return 0;
}
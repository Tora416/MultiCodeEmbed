#include <stdio.h>

int main()
{
    int n;
    float nota, notafinal = 0, denominador = 0, fator, notamedia;

    printf("\nInforme a quantidade de notas do aluno: ");
    scanf("%i", &n);

    for (int qtd = 1; qtd <= n; qtd++)
    {
        printf("\nInforme a %iª nota: ", qtd);
        scanf("%f", &nota);

        if ((qtd % 2) == 0)
        {
            fator = 3;
            nota = fator * nota;
        }

        else
        {
            fator = 2;
            nota = fator * nota;
        }

        notafinal = notafinal + nota;
        denominador = denominador + fator;
    }

    notamedia = notafinal / denominador;
    printf("\nNota média = %.2f\n\n", notamedia);

    return 0;
}
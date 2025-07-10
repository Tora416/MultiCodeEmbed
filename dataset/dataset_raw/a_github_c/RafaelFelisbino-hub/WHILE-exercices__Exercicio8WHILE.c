

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

int main() 
{
    int  numeroDivisivel = 0, inicioIntervalo = 0, fimIntervalo = 0, qtdDivisoesExatas = 0,soma = 0;

    setlocale(LC_ALL, "Portuguese");
    system("color 17");

    printf("Digite o número que queira dividir:  ");
    scanf_s("%i", &numeroDivisivel);

    printf("Digite o primeiro intervalo:  ");
    scanf_s("%i", &inicioIntervalo);

    printf("Digite o segundo intervalo:  ");
    scanf_s("%i", &fimIntervalo);

    while (inicioIntervalo <= fimIntervalo)
    {
        if (inicioIntervalo % numeroDivisivel == 0)
        {
            qtdDivisoesExatas++;
            soma += inicioIntervalo;
        }
        inicioIntervalo++;
    }

    printf("\n\nO número pode ser dividido por %i números inteiros\n\n", qtdDivisoesExatas);
    printf("A soma dos números inteiros divididos por %i é:  %i\n\n",numeroDivisivel, soma);

    system("pause");
}

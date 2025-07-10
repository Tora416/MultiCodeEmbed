

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

float calculaDesvioPadrao(float vet[]);

int main()
{
        int i;

        float vet[10];


        for (i = 0; i < 10; ++i){

            printf("Digite um numero: ");
            scanf("%f", &vet[i]);
        }
            printf("\n Desvio Padrao = %.6f", calculaDesvioPadrao(vet));

            system("PAUSE");
            return 0;
}

    float calculaDesvioPadrao(float vet[]) {

        float soma = 0.0, mean, desvio = 0.0;
        int i;

        for (i = 0; i < 10; i++) {
            soma += vet[i];
        }

        mean = soma / 10;
        for (i = 0; i < 10; i++)
            desvio += pow(vet[i] - mean, 2);
        return sqrt(desvio / 10);
}

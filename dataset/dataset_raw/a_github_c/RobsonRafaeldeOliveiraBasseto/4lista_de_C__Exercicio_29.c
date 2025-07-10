

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

int quantidadeTotalPar = 0;
int quantidadeTotalImpar = 0;
int pares[6];
int impares[6];

void calcularTotal(int numero[6]) {

    for (int i = 0; i < 6; i++) {

        if (numero[i] % 2 == 0) {

            quantidadeTotalPar = quantidadeTotalPar + numero[i];
            pares[i] = numero[i];

        } else {

            quantidadeTotalImpar = quantidadeTotalImpar + numero[i];
            impares[i] = numero[i];

        }
    }
}

void imprimirResultados() {

    printf("Soma total numeros pares digitados: %d\n\n", quantidadeTotalPar);
    printf("Valores pares digitados: \n");

    for (int i = 0; i < 6; i++) {

        if (pares[i] > 0) {

            printf("%d\n", pares[i]);
        }
    }

    printf("Soma total numeros impares digitados: %d\n\n", quantidadeTotalImpar);
    printf("Valores impares digitados: \n");

    for (int i = 0; i < 6; i++) {

        if (impares[i] > 0) {

            printf("%d\n", impares[i]);
        }
    }

}

int main() {
    setlocale(LC_ALL, "");
    int numero[6];

    for (int i = 0; i < 6; i++) {

        printf("Preencha o valor numero %d\n", i);
        scanf("%d", &numero[i]);
    }

    system("cls");

    calcularTotal(numero);
    imprimirResultados();

    return 0;
}

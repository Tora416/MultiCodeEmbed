

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

int vetor[15];

void compactarVetor() {
    for (int i = 0; i < 15; i++) {

        if (vetor[i] == 0) {

            for (int j = i; j < 15; j++) {

                vetor[j] = vetor[j + 1];
            }
        }
    }
}

void imprimirVetor() {

    for (int i = 0; i < 15; i++) {

        if (vetor[i] != 0) {
            printf("Posicao %d valor do vetor: %d\n", i, vetor[i]);
        }
    }
}

int main() {
    setlocale(LC_ALL, "");

    for (int i = 0; i < 15; i++) {

        printf("Preencha o valor do vetor1 numero %d\n", i);
        scanf("%d", &vetor[i]);
    }

    system("cls");

    compactarVetor();
    imprimirVetor();

    return 0;
}





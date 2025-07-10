

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

int vet1[10];
int vet2[10];
int uniao[20];

void populaVetorUniao() {

    for (int c = 0; c < 10; c++) {
        uniao[c] = vet1[c];
    }

    for (int i = 0; i <= 10; i++) {
        int valorJaInseridoUniao = 0;

        for (int j = 0; j < 10; j++) {

            if (vet2[i] == uniao[j]) {
                valorJaInseridoUniao = 1;
            }
        }

        if (valorJaInseridoUniao == 0) {
            uniao[i + 10] = vet2[i];
        }
    }
}

int verificarValorRepetido(int valorComparar) {

    for (int i = 0; i < 10; i++) {

        if (vet1[i] == valorComparar) {
            return valorComparar;
        }

        if (vet2[i] == valorComparar) {
            return valorComparar;
        }

    }

    return 0;
}

void imprimirVetores() {

    for (int i = 0; i < 20; i++) {

        printf("%d\n", uniao[i]);
    }
}

int main() {
    setlocale(LC_ALL, "");

    for (int i = 0; i < 10; i++) {

        int valorAlocar = 0;

        printf("Preencha o valor do vetor1 numero %d\n", i);
        scanf("%d", &valorAlocar);

        int retorno = verificarValorRepetido(valorAlocar);

        if (retorno != 0) {

            printf("O valor %d nao pode ser inserido pois esta repetido, por favor informe outro numero.", retorno);
            i--;
            continue;
        } else {

            vet1[i] = valorAlocar;
        }
    }

    for (int i = 0; i < 10; i++) {

        int valorAlocar = 0;

        printf("Preencha o valor do vetor2 numero %d\n", i);
        scanf("%d", &valorAlocar);

        int retorno = verificarValorRepetido(valorAlocar);

        if (retorno != 0) {

            printf("O valor %d nao pode ser inserido pois esta repetido, por favor informe outro numero.\n", retorno);
            i--;
            continue;
        } else {

            vet2[i] = valorAlocar;
        }
    }

    system("cls");

    printf("\n ------------------------------ \n");

    populaVetorUniao();

    printf("--- Uniao entre vetores ---\n");

    imprimirVetores(uniao, 10);

    printf("--------------------------------\n");

    return 0;
}



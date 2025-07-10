

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

int vet1[10];
int vet2[10];
int intersecao[10];

void criarVetorIntersecao() {

    for (int i = 0; i < 10; i++) {

        for (int j = 0; j < 10; j++) {

            if (vet1[i] == vet2[j]) {
                intersecao[i] = vet1[i];
            }
        }
    }
}

int verificarValorRepetido(int vet1[10], int valorComparar) {

    for (int i = 0; i < 10; i++) {

        if (vet1[i] == valorComparar) {
            return valorComparar;
        }

    }

    return 0;
}

void imprimirVetorIntersecao() {

    for (int i = 0; i < 10; i++) {

        if (intersecao[i] > 0) {

            printf("%d\n", intersecao[i]);
        }
    }
}

int main() {
    setlocale(LC_ALL, "");

    for (int i = 0; i < 10; i++) {

        int valorAlocar = 0;

        printf("Preencha o valor do vetor1 numero %d\n", i);
        scanf("%d", &valorAlocar);

        int retorno = verificarValorRepetido(vet1, valorAlocar);

        if (retorno != 0) {

            printf("O valor %d nao pode ser inserido pois esta repetido, por favor informe outro numero.\n", retorno);
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

        int retorno = verificarValorRepetido(vet2, valorAlocar);

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

    criarVetorIntersecao();
    imprimirVetorIntersecao();

    return 0;
}


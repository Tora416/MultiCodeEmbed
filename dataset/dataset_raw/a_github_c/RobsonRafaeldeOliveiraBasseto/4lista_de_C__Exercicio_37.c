

#include <stdio.h>
#include <stdlib.h>

int vetor[11];
int posicaoReporNumero;

void ordenarVetorCrescente() {

    for (int i = 0; i <= 5; i++) {

        int menorValorPosicao = buscarMenorValor(i);

        int valorPosicaoAnterior = vetor[i];
        vetor[i] = menorValorPosicao;
        vetor[posicaoReporNumero] = valorPosicaoAnterior;
    }
}

void ordenarVetorDecrescente() {

    for (int i = 6; i <= 11; i++) {

        int maiorValorPosicao = buscarMaiorValor(i);

        int valorPosicaoAnterior = vetor[i];
        vetor[i] = maiorValorPosicao;
        vetor[posicaoReporNumero] = valorPosicaoAnterior;
    }
}

int buscarMenorValor(int j) {

    int valorAAssumirPosicao = vetor[j];
    posicaoReporNumero = NULL;

    for (int i = j; i < 11; i++) {

        if (valorAAssumirPosicao > vetor[i]) {

            valorAAssumirPosicao = vetor[i];
            posicaoReporNumero = i;
        }
    }

    return valorAAssumirPosicao;
}

int buscarMaiorValor(int j) {

    int valorAAssumirPosicao = vetor[j];
    posicaoReporNumero = NULL;

    for (int i = j; i < 11; i++) {

        if (valorAAssumirPosicao < vetor[i]) {

            valorAAssumirPosicao = vetor[i];
            posicaoReporNumero = i;
        }
    }

    return valorAAssumirPosicao;
}

void imprimirVetor() {

    for (int i = 0; i < 11; i++) {

        printf("Posicao %d valor do vetor: %d\n", i, vetor[i]);
    }
}

int main()
{
    for (int i = 0; i < 11; i++){
        printf("Preencha o valor do vetor numero %d\n", i);
        scanf("%d", &vetor[i]);
    }

    ordenarVetorCrescente();
    ordenarVetorDecrescente();
    imprimirVetor();

    return 0;
}


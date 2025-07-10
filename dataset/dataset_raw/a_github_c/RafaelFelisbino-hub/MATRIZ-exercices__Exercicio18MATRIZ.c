

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() 
{
    char nomesProdutos[5][100], nomeCaro[100], loja[4][20] = {"Adidas","Nike","Cervejaria","Cachoeiras"};
    float lojaProduto[4][5], matrizImpostos[4][5], maisCaro = 0;
    int i, j;

    for (i = 0; i < 5; i++)
    {
        printf("Digite os nomes dos produtos [%d]:  ", i);
        scanf_s("%[^\n]s", &nomesProdutos[i], 100);
        getchar();
    }
    
    for (i = 0; i < 4; i++)
        for (j = 0; j < 5; j++) 
        {
            printf("Digite o preco dos produtos [%s] loja [%s] produto:  ", loja[i], nomesProdutos[j]);
            scanf_s("%f", &lojaProduto[i][j]);
        }

    for (i = 0; i < 4; i++)
        for (j = 0; j < 5; j++)
        {
            if (lojaProduto[i][j] <= 50) 
                matrizImpostos[i][j] = lojaProduto[i][j] * 5 / 100 + lojaProduto[i][j];
            if(lojaProduto[i][j] > 50 && lojaProduto[i][j] <= 100)
                matrizImpostos[i][j] = lojaProduto[i][j] * 10 / 100 + lojaProduto[i][j];
            if (lojaProduto[i][j] > 100)
                matrizImpostos[i][j] = lojaProduto[i][j] * 20 / 100 + lojaProduto[i][j];
        }

    for (i = 3; i < 4; i++)
        for (j = 0; j < 5; j++) 
        {
            if (matrizImpostos[i][j] > maisCaro) 
            {
                maisCaro = matrizImpostos[i][j];
                nomeCaro[99] = strcpy_s(nomeCaro, 99, nomesProdutos[i]);
            }
        }

    for (i = 0; i < 4; i++)
        for (j = 0; j < 5; j++)
        {
            printf("A matriz com os impostos [%d][%d]:  %.2f\n", i, j, matrizImpostos[i][j]);
        }

    printf("O produto mais caro da 3 linha e %s com o valor de %.0f\n", nomeCaro, maisCaro);

    system("pause");
}

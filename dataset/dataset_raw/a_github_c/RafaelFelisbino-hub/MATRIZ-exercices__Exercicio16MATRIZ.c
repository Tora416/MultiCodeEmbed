

#include <stdio.h>
#include <stdlib.h>

int main() 
{
    int vetorA[5], vetorB[5], matrizC[2][5], i , j;

    for (i = 0; i < 5; i++)
    {
        printf("Informe os valores do vetor A:  ");
        scanf_s("%i", &vetorA[i]);
    }
        
    for (i = 0; i < 5; i++) 
    {
        printf("Informe os valores do vetor B:  ");
        scanf_s("%i", &vetorB[i]);
    }
    
    for (j = 0; j < 5; j++)
    {
        matrizC[0][j] = vetorA[j];
        matrizC[1][j] = vetorB[j];
    }
    
    for (i = 0; i < 2; i++)
        for (j = 0; j < 5; j++)
            printf("A matriz com os vetores A e B e: %d linha,  %d coluna  %i\n", i, j, matrizC[i][j]);
        
        
    

    system("pause");
}
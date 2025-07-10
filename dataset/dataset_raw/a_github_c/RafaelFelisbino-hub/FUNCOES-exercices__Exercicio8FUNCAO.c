

#include <stdio.h>
#include <stdlib.h>

void metade();

float A[30], B[30];

int main() 
{
    int i;

    for (i = 0; i < 30; i++) 
    {
        printf("Digite os valores de A:  ");
        scanf_s("%f", &A[i]);

        metade();
    }
    
    for (i = 0; i < 30; i++)
        printf("Os valores de A pela metade sao:  %.2f\n", B[i]);
}

void metade() 
{
    int i;
    
    for (i = 0; i < 30; i++) 
    {
        B[i] = A[i] / 2;
    }
}


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <locale.h>


int main()
{
    int N1, N2, impar = 0, n3,i,r;

    setlocale(LC_ALL, "Portuguese");
    
    system("color 17");

    printf("Digite o valor de N1:  ");
    scanf_s("%i", &N1);

    printf("\nDigite o valor de N2:  ");
    scanf_s("%i", &N2);

    for (i =N1++ ; i < N2; i++)
    {
        if (i % 2 == 1) 
        {
            impar++;
        }
        
    }
    printf("\nExistem %i numeros ímpares entre N1 e N2 mano, ÉOBIXO\n", impar);

    system("pause");
}

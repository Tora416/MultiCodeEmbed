#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>


int main() 
{

    int i;
    int num = 0;
    int inter1=0, inter2=0, inter3=0, inter4=0;
    

    system("color 17");

    for (i = 1; i <= 10; i++) {

        printf("\n%d - Digite os numeros:  ", i);
        scanf_s("%i", &num);

        if (num < 0) 
        {
            printf("Numero invalido\n");
            break;
        }
        
        if ((num > 0) && (num <= 25))
        {
            
            inter1++;
        }

        if ((num > 25) && (num <= 50))
        {

            inter2++;
        }

        if ((num > 50) && (num <= 75))
        {

            inter3++;
        }

        if ((num > 75) && (num <= 100))
        {

            inter4++;
        }

    }

    printf("Os numeros no 1 intervalo sao:  %i\n", inter1);
    printf("Os numeros no 2 intervalo sao:  %i\n", inter2);
    printf("Os numeros no 3 intervalo sao:  %i\n", inter3);
    printf("Os numeros no 4 intervalo sao:  %i\n", inter4);
    

    system("pause");



}
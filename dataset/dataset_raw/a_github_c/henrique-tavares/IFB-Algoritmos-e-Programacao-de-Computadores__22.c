#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#define true 1
#define false 0

int main()
{
    char str[10];
    int tam, valor, num = false;
    while (num == false)
    {
        puts("\nInforme um número:");
        scanf("%s", str);
        getchar();

        tam = strlen(str);
        valor = atoi(str);
        

        if ((pow(10, (tam - 1))) <= valor)
        {
            num = true;
        }

        else if (num == false)
        {
            system("clear");
            puts("\nNúmero inválido, digite novamente!");
        }
    }

    puts("\nO número é de fato um número\n");
    return 0;
}
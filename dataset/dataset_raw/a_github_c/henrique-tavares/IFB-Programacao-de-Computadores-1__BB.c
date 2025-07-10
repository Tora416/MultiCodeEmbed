#include <stdio.h>
#include <math.h>
#include <string.h>

int main()
{
    char str[31];
    long int tam, soma = 0, pot;

    fgets(str, 31, stdin);

    for (int i=0; str[i] != '\0'; i++)
    {
        if (str[i] == '\n')
        {
            str[i] = '\0';
        }
    }

    tam = strlen(str);
    pot = tam-1;

    for (int i=0; i<tam; i++)
    {
        if (str[i] == '1')
        {
            soma += pow(2,(pot-i));
        }
    }

    printf("%li\n", soma);

    return 0;
}
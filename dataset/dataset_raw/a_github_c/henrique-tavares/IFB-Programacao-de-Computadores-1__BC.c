#include <stdio.h>
#include <math.h>
#include <string.h>

int main()
{
    char hex[9];
    long int soma = 0;
    int tam, pot;

    fgets(hex, 9, stdin);

    for (int i = 0; hex[i] != '\0'; i++)
    {
        if (hex[i] == '\n')
        {
            hex[i] = '\0';
        }
    }

    tam = strlen(hex);
    pot = tam - 1;

    for (int i = 0; hex[i] != '\0'; i++)
    {
        switch (hex[i])
        {
        case '1':
            soma += 1 * pow(16, (pot - i));
            break;

        case '2':
            soma += 2 * pow(16, (pot - i));
            break;

        case '3':
            soma += 3 * pow(16, (pot - i));
            break;

        case '4':
            soma += 4 * pow(16, (pot - i));
            break;

        case '5':
            soma += 5 * pow(16, (pot - i));
            break;

        case '6':
            soma += 6 * pow(16, (pot - i));
            break;

        case '7':
            soma += 7 * pow(16, (pot - i));
            break;

        case '8':
            soma += 8 * pow(16, (pot - i));
            break;

        case '9':
            soma += 9 * pow(16, (pot - i));
            break;

        case 'a':
            soma += 10 * pow(16, (pot - i));
            break;

        case 'b':
            soma += 11 * pow(16, (pot - i));
            break;

        case 'c':
            soma += 12 * pow(16, (pot - i));
            break;

        case 'd':
            soma += 13 * pow(16, (pot - i));
            break;

        case 'e':
            soma += 14 * pow(16, (pot - i));
            break;

        case 'f':
            soma += 15 * pow(16, (pot - i));
            break;

        }
    }

    printf("%li\n", soma);

    return 0;
}
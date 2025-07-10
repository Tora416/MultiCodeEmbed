#include <stdio.h>
#include <string.h>
#define true 1
#define false 0

int main()
{
    char str[1001], aux;
    int qtd = 1;

    fgets(str, 1001, stdin);

    for (int i = 0; str[i] != '\0'; i++)
    {
        if (str[i] == '\n')
        {
            str[i] = '\0';
        }
    }

    for (int i = 0; str[i] != '\0';)
    {
        aux = str[i];

        for (int k = 1; str[k] != '\0'; k++)
        {
            if (aux != str[i + k])
            {
                break;
            }
            else
            {
                qtd++;
            }
            
        }

        i += qtd;

        if (qtd == 1)
        {
            printf("%c", aux);
        }
        
        else
        {
            printf("%i%c", qtd, aux);
        }
        
        qtd = 1;
    }

    putchar('\n');
    return 0;
}
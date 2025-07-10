#include <stdio.h>
#include <string.h>
#define true 1
#define false 0

int main()
{
    char string[81], stringinv[81], aux;
    int tam, tam1, busca;

    fgets(string, 81, stdin);

    for (int i=0; string[i] != '\0'; i++)
    {
        if (string[i] == '\n')
        {
            string[i] = '\0';
        }
    }

    for (int i = 0; string[i] != '\0'; i++)
    {
        if (string[i] == ' ')
        {
            for (int j = i; string[j] != '\0'; j++)
            {
                string[j] = string[j + 1];
            }
        }
    }

    tam = strlen(string);

    for (int i = 0; string[i] != '\0'; i++)
    {
        stringinv[i] = string[(tam - 1) - i];
    }

    busca = true;
    
    for (int i = 0; string[i] != '\0'; i++)
    {
        if (string[i] != stringinv[i])
        {
            busca = false;
            break;
        }
    }

    if (busca == true)
    {
        printf("S\n");
    }
    else if (busca == false)
    {
        printf("N\n");
    }

    return 0;
}
#include <stdio.h>
#include <string.h>
#define true 1
#define false 0

void fill_letters(char str[], char letters[])
{
    int busca, tam;

    letters[0] = str[0];
    for (int i = 0; str[i] != '\0'; i++)
    {
        busca = false;
        for (int j = 0; (letters[j] != '\0') && (busca == false); j++)
        {
            if (letters[j] == str[i])
            {
                busca = true;
            }
        }
        if (busca == false)
        {
            tam = strlen(letters);
            letters[tam] = str[i];
            letters[tam + 1] = '\0';
        }
    }
}

int main()
{
    char str[100002], letters[100002];
    int qtd, tam_s, impar = false, pali = true;

    fgets(str, 100002, stdin);

    if (str[strlen(str) - 1] == '\n')
    {
        str[strlen(str) - 1] = '\0';
    }

    fill_letters(str, letters);
    tam_s = strlen(str);

    for (int i = 0; (letters[i] != '\0') && (pali == true); i++)
    {
        qtd = 0;
        for (int j = 0; str[j] != '\0'; j++)
        {
            if (letters[i] == str[j])
            {
                qtd++;
            }
        }

        if (tam_s % 2 == 0)
        {
            if (qtd % 2 != 0)
            {
                pali = false;
            }
        }
        else
        {
            if (qtd % 2 != 0)
            {
                if (impar == false)
                {
                    impar = true;
                }
                else if (impar == true)
                {
                    pali = false;
                }
            }
        }    
    }

    if (pali == true)
    {
        printf("Sim\n");
    }

    else
    {
        printf("Nao\n");
    }

    return 0;
}
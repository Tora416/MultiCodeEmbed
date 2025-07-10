#include <stdio.h>
#include <string.h>
#define true 1
#define false 0

int main()
{
    char frase[200], termo[200];
    int i = 0, tam_frase, tam_termo, busca = false, indice;
    puts("\nInforme uma frase:");
    scanf("%[^\n]s", frase);
    getchar();
    puts("\nInforme um termo:");
    scanf("%[^\n]s", termo);

    tam_frase = strlen(frase);
    tam_termo = strlen(termo);

    if (tam_frase >= tam_termo)
    {
        for (int i = 0; i < tam_frase; i++)
        {
            if ((frase[i] == termo[0]) && (busca == false))
            {
                busca = true;
                indice = i;
                for (int j = 0; j < tam_termo; j++)
                {
                    if ((frase[i + j] != termo[j]) && (busca == true))
                    {
                        busca = false;
                    }
                }
            }
        }
    }
    if (busca == true)
    {
        printf("\nTermo encontrado, iniciando-se na posição %i\n\n", indice + 1);
    }
    else if (busca == false)
    {
        puts("\nTermo não encontrado na frase\n");
    }
    return 0;
}
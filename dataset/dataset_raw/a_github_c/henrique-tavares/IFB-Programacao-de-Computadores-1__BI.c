#include <stdio.h>
#include <string.h>
#define true 1
#define false 0

int main()
{
    char str0[1002], str[1002], aux[1002];
    int qtd = 0, tam, busca, busca1, tam0, tam1, tam2, p2, p1, k1, h1;

    scanf("%1002[^\n]s", str);

    tam = strlen(str);

    for (int i = (tam / 2); i > 1; i--)
    {
        for (int h = 0; str[(2 * i) + h - 1] != '\0'; h++)
        {
            h1 = h;
        }
        
        for (int h = h1; h >= 0; h--)
        {
            for (int j = 0; j < i; j++)
            {
                aux[j] = str[j + h];
            }

            tam0 = strlen(aux);
            for (int j = 0; j < tam0; j++)
            {
                if (((int)aux[j] < 97) || ((int)aux[j] > 122))
                    aux[j] = '\0';
            }

            tam0 = strlen(aux);
            

            printf("\n%s %i\n", aux, tam0);

            for (int k = 0; str[2 * i - 1 + k + h] != '\0'; k++)
            {
                k1 = k;
            }

            for (int k = k1; k >= 0; k--)
            {
                busca = true;
                for (int l = 0; ((l < tam0)&&(busca == true)); l++)
                {
                    

                    if (aux[l] != str[i + k + l + h])
                    {
                        busca = false;
                    }
                    p2 = i + k + l + h;
                    p1 = i + k + h;
                }

                if (busca == true)
                {
                    if (str[p2 + 1] == '\0')
                    {
                        for (int j = p2; j >= p1; j--)
                        {
                            str[j] = '\0';
                        }
                    }

                    else
                    {
                        for (int j = p1; (j <= p2)||(str[j+tam0] != '\0'); j++)
                        {                           
                            str[j] = str[j + tam0];
                            str[j + tam0] = '\0';

                            
                        }
                    }
                    qtd ++;
                    printf("\ntrue %i %i\n%s\n", p1, p2, aux);
                }

                
            }

            for (int j = tam0 - 1; j >= 0; j--)
            {
                aux[j] = '\0';
            }
        }
    }

    printf("\n%s %li %i\n", str, strlen(str), qtd);
    printf("%li\n", strlen(str) + qtd);

    return 0;
}
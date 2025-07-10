#include <stdio.h>
#include <string.h>
#define true 1
#define false 0

int main()
{
    char str[1001], aux[1002], aux2[1002];
    int tam, tam2, tam3, busca;

    scanf("%1001[^\n]s", str);
    tam = strlen(str);

    for (int i = 1; i < tam; i++)
    {
        for (int j = 0; j <= i; j++)
        {
            aux[j] = str[j];
        }

        tam2 = strlen(aux);
        for (int j = 0; j < tam2; j++)
        {
            if ((int) aux[j] != (int) str[j])
                aux[j] = '\0';
            
            
        }
        tam2 = strlen(aux);
        printf("%s %i\n", aux, tam2);

        for (int j = tam2 - 2; j > 0; j--)
        {
            for (int k = 0; aux[j + k] != '\0'; k++)
            {
                
                for (int l = k; (l <= j + k)&&(str[l + tam2] != '\0'); l++)
                {
                    printf("%c %c\n", aux[l], str[l + j]);
                }
                putchar('\n');
            }
        }
        
        for (int j = tam2 - 1; j <= 0; j--)
        {
            aux[j] = '\0';
        } 
    }

    return 0;
}
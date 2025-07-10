#include <stdio.h>
#include <string.h>

int main()
{
    char nome1[100], sobrenome1[100], nome2[100], sobrenome2[100], sobrenome2_2[100];
    int i1, j1, i2, j2, i1_2, tam_sobrenome1, tam_sobrenome2;

    printf("\nInforme o 1º nome: ");
    scanf("%[^\n]s", nome1);
    getchar();
    printf("\nInforme o 1º sorenomenome: ");
    scanf("%[^\n]s", sobrenome1);
    getchar();
    printf("\nInforme o 2º nome: ");
    scanf("%[^\n]s", nome2);
    getchar();
    printf("\nInforme o 2º sobrenome: ");
    scanf("%[^\n]s", sobrenome2);
    getchar();

    strcpy(sobrenome2_2, sobrenome2);

    tam_sobrenome1 = strlen(sobrenome1);
    i1 = tam_sobrenome1;
    while (sobrenome1[i1] != ' ')
    {
        i1--;
    }
    i1_2 = i1 + 1;

    tam_sobrenome2 = strlen(sobrenome2);
    j1 = 0;
    while (sobrenome2[j1] != ' ')
    {
        j1++;
    }

    for (int k = (j1 + 1); k <= (j1 + i1); k++)
    {
        sobrenome2[k] = sobrenome1[i1_2];
        i1_2++;
    }

    printf("\n%s %s e %s %s.\nApós casados se chamarão:\n%s %s e %s %s\n\n",
           nome1, sobrenome1, nome2, sobrenome2_2, nome1, sobrenome2, nome2, sobrenome2);
    return 0;
}
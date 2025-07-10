#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    FILE *arq;
    char aux, *texto;
    float res = 0;

    if (argc < 2)
    {
        printf("\nErro! Não foi informado o nome do arquivo.\n\n");
        return 0;
    }

    arq = fopen(argv[1], "r");

    if (arq == NULL)
    {
        printf("\nErro ao abrir o arquivo.\n\n");
        return 0;
    }

    int i = 0;

    while (fscanf(arq, "%c", &aux) != EOF)
    {
        i++;
    }

    rewind(arq);

    

    texto = malloc(i * sizeof(char));

    for (int j = 0; j < i; j++)
    {
        fscanf(arq, "%c", texto+j);
    }

    for (int j = 0; j < i; j++)
    {
        if (texto[j] == 'R' && texto[j+1] == '$')
        {
            res += atof(texto + j+2);
        }
    }
    printf("\nLista de compras: R$%.2f\n\n", res);

    return 0;
}
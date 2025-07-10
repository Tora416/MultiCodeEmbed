#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    FILE *arq_1, *arq_2;
    char aux, *texto;

    if (argc < 3)
    {
        printf("\nErro! Não foram informados aquivos o suficiente.\n\n");
        return 0;
    }

    arq_1 = fopen(argv[1], "r");
    arq_2 = fopen(argv[2], "w");

    if (arq_1 == NULL || arq_2 == NULL)
    {
        printf("\nErro ao abrir algum arquivo.\n\n");
        return 0;
    }

    int i = 0;
    while (fscanf(arq_1, "%c", &aux) != EOF)
    {
        i++;
    }

    rewind(arq_1);

    texto = malloc(i+1 * sizeof(char));

    for (int j = 0; j < i; j++)
    {
        fscanf(arq_1, "%c", texto + j);
    }
    texto[i] = '\0';

    for (int j = 0; j < i; j++)
    {
        if (texto[j] == '/' && texto[j+1] == '/')
        {
            int k = j;
            while (texto[k] != '\n' && texto[k] != '\0')
            {
                texto[k] = ' ';
                k++;
            }
        }

    }

    fprintf(arq_2, "%s", texto);

    fclose(arq_1);
    fclose(arq_2);

    return 0;
}
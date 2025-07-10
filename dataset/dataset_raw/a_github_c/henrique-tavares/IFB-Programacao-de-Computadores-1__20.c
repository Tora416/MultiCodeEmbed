#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    FILE *arq;
    char aux, *texto;

    if (argc < 2)
    {
        printf("\nErro! Não foi informado o nome do arquivo.\n\n");
        return 0;
    }

    arq = fopen(argv[1], "r+");

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

    texto = malloc((i+1) * sizeof(char));

    rewind(arq);

    i = 0;

    while (fscanf(arq, "%c", &aux) != EOF)
    {
        texto[i] = aux;
        i++;
    }
    texto[i] = '\0';


    for (int j = 0; j < i; j++)
    {
        switch (texto[j])
        {
            case 'a':
                texto[j] = 'A';
                break;
                
            case 'e':
                texto[j] = 'E';
                break;

            case 'i':
                texto[j] = 'I';
                break;

            case 'o':
                texto[j] = 'O';
                break;

            case 'u':
                texto[j] = 'U';
                break;
            
            default:
                break;
        }
    }

    rewind(arq);
    fprintf(arq, "%s", texto);
    fclose(arq);

    return 0;
}
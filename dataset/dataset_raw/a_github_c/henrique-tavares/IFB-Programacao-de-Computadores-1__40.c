#include <stdio.h>
#include <stdlib.h>

typedef enum Bool
{
    false, true

} bool;

typedef struct Quantidade
{
    int chars;
    int linhas;
    int palavras;

} qtd_t;

int main(int argc, char **argv)
{
    FILE *arq;
    char aux;
    qtd_t qtd;
    bool espaco = false, pontuacao = false, enter = false;
    
    qtd.chars = 0;
    qtd.linhas = 1;
    qtd.palavras = 0;

    if (argc < 2)
    {
        printf("\nErro! Não foram informados arquivos o suficiente\n\n");
        return 0;
    }

    arq = fopen(argv[1], "r");

    if (arq == NULL)
    {
        printf("\nErro ao abrir o arquivo.\n\n");
        return 0;
    }

    for (int i = 0; fscanf(arq, "%c", &aux) != EOF; i++)
    {
        if (aux == '\n')
        {
            qtd.linhas++;
        }

        if (i == 0)
        {
            if (aux != ' ' && aux != '\n' && aux != ',' && aux != '.' && aux != ';' && aux != ':' && aux != '?' && aux != '!')
            {
                qtd.chars++;
                qtd.palavras++;
            }
        }

        else
        {
            if (aux == ' ')
            {
                espaco = true;
            }

            else if (aux == ',' || aux == '.' || aux == ';' || aux == ':' || aux == '?' || aux == '!')
            {
                pontuacao = true;
            }

            else if (aux == '\n')
            {
                enter = true;
            }

            else
            {
                qtd.chars++;
            }

            if ((espaco == true || pontuacao == true || enter == true) &&\
                (aux != ' ' && aux != '\n' && aux != ',' && aux != '.' && aux != ';' && aux != ':' && aux != '?' && aux != '!'))
                {
                    qtd.palavras++;

                    espaco = false;
                    pontuacao = false;
                    enter = false;
                }
        }
    }

    printf("\n%s:\n", argv[1]);
    printf("\t-> chars: %i\n", qtd.chars);
    printf("\t-> palavras: %i\n", qtd.palavras);
    printf("\t-> linhas: %i\n", qtd.linhas);

    return 0;
}
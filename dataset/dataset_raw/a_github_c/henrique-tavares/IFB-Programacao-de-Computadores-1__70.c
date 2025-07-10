#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Aluno
{
    char nome[32];
    int semestre;
    float ra;

} aluno_t;

void imprime_sem(aluno_t *alunos, int x, int n)
{
    for (int i = 0; i < n; i++)
    {
        if (alunos[i].semestre == x)
        {
            printf("\nNome: %s\n", alunos[i].nome);
            printf("Semestre: %i\n", alunos[i].semestre);
            printf("Rendimento acadêmico: %f\n", alunos[i].ra);
        }
    }
}

int main(int argc, char **argv)
{
    FILE *arq;
    aluno_t *alunos;
    char aux;
    int x;

    if (argc < 2)
    {
        printf("\nErro! Não foi informado o nome do arquivo.\n\n");
        return 0;
    }

    arq  = fopen(argv[1], "r");

    if (arq == NULL)
    {
        printf("\nErro ao abrir o arquivo.\n\n");
        return 0;
    }

    int i = 1;
    while (fscanf(arq, "%c", &aux) != EOF)
    {
        if (aux == '\n')
        {
            i++;
        }
    }

    rewind(arq);

    if (i % 3 == 0)
    {
        i /= 3;
    }
    
    else
    {
        printf("\nInformações insuficientes.\n\n");
        return 0;
    }

    alunos = malloc(i * sizeof(aluno_t));

    for (int j = 0; j < i; j++)
    {
        fscanf(arq, "%s", alunos[j].nome);
        fscanf(arq, "%i", &alunos[j].semestre);
        fscanf(arq, "%f", &alunos[j].ra);
    }

    printf("\nDigite um semestre: ");
    scanf("%i", &x);
    getchar();

    imprime_sem(alunos, x, i);

    fclose(arq);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Aluno
{
    char nome[102];
    int prova[3];
    int trab[2];

} aluno_t;

void insere_aluno(FILE *arq)
{
    aluno_t aluno;
    int tam;

    printf("\nDigite o nome do aluno: ");
    fgets(aluno.nome, 102, stdin);

    tam = strlen(aluno.nome);

    if (aluno.nome[tam - 1] == '\n')
    {
        aluno.nome[tam - 1] = '\0';
    }

    printf("Digite a nota da primeira prova: ");
    scanf("%i", aluno.prova[0]);
    getchar();

    printf("Digite a nota da segunda prova: ");
    scanf("%i", aluno.prova[1]);
    getchar();

    printf("Digite a nota da terceira prova: ");
    scanf("%i", aluno.prova[2]);
    getchar();

    printf("Digite a nota do primeiro trabalho: ");
    scanf("%i", aluno.trab[0]);
    getchar();

    printf("Digite a nota do segundo trabalho: ");
    scanf("%i", aluno.trab[1]);
    getchar();

    fseek(arq, 0, SEEK_END);
    
    fwrite(&aluno, sizeof(aluno), 1, arq);
}

void exibe_alunos(FILE *arq)
{
    aluno_t aluno;

    while (fread(&aluno, sizeof(aluno_t), 1, arq) != 0)
    {
        printf("\nNome: %s\n", aluno.nome);
        printf("\t-> Prova 1: %i\n", aluno.prova[0]);
        printf("\t-> Prova 2: %i\n", aluno.prova[1]);
        printf("\t-> Prova 3: %i\n", aluno.prova[3]);
        printf("\t-> Trabalho 1: %i\n", aluno.trab[0]);
        printf("\t-> Trabalho 2: %i\n", aluno.trab[1]);
    }
}

void exibe_aprovados(FILE *arq)
{
    aluno_t aluno;
    int media;

    while (fread(&aluno, sizeof(aluno_t), 1, arq) != 0)
    {
        media = ((aluno.prova[0] * 2) + (aluno.prova[1] * 3) + (aluno.prova[2] * 3) + (aluno.trab[0] + aluno.trab[1])) / 10;

        if (media >= 6.0)
        {
            printf("\nNome: %s\n", aluno.nome);
            printf("\t-> Prova 1: %i\n", aluno.prova[0]);
            printf("\t-> Prova 2: %i\n", aluno.prova[1]);
            printf("\t-> Prova 3: %i\n", aluno.prova[3]);
            printf("\t-> Trabalho 1: %i\n", aluno.trab[0]);
            printf("\t-> Trabalho 2: %i\n", aluno.trab[1]);
        }
    }
}

void exibe_reprovados(FILE *arq)
{
    aluno_t aluno;
    int media;

    while (fread(&aluno, sizeof(aluno_t), 1, arq) != 0)
    {
        media = ((aluno.prova[0] * 2) + (aluno.prova[1] * 3) + (aluno.prova[2] * 3) + (aluno.trab[0] + aluno.trab[1])) / 10;

        if (media < 6.0)
        {
            printf("\nNome: %s\n", aluno.nome);
            printf("\t-> Prova 1: %i\n", aluno.prova[0]);
            printf("\t-> Prova 2: %i\n", aluno.prova[1]);
            printf("\t-> Prova 3: %i\n", aluno.prova[3]);
            printf("\t-> Trabalho 1: %i\n", aluno.trab[0]);
            printf("\t-> Trabalho 2: %i\n", aluno.trab[1]);
        }
    }
}

int main(int argc, char **argv)
{
    FILE *arq;
    int escolha;
    aluno_t aluno;

    if (argc < 2)
    {
        printf("\nErro! Não foi informado o arquivo.\n\n");
        return 0;
    }

    arq = fopen(argv[1], "r+b");

    if (arq == NULL)
    {
        printf("\nErro ao abrir o arquivo,\n\n");
        return 0;
    }

    do
    {
        printf("\n\t(1) Inserir alunos e suas respectivas notas\n");
        printf("\t (2) Exibir alunos e suas respectivas notas\n");
        printf("\t (3) Exibir alunos aprovados\n");
        printf("\t (4) Exibir alunos reprovados\n");
        printf("\t (5) Sair\n");
        printf('\n\t Digite sua escolha: ');
        scanf("%i", &escolha);
        getchar();
        system("clear");

        switch (escolha)
        {
            case 1:
                insere_aluno(arq);
                break;

            case 2:
                exibe_alunos(arq);
                break;

            case 3:
                exibe_aprovados(arq);
                break;
            
            case 4:
                exibe_reprovados(arq);
                break;
            
            case 5:
                return 0;
            
            default:
                break;
        }

        printf("\nPressione ENTER para continuar: ");
        getchar();
        system("clear");

    } while (escolha != 5);

    return 0;
}
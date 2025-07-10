#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum Bool
{
    false, true
    
} bool;

typedef struct Aluno
{
    char nome[82];
    int idade;
    int semestre;
    float renda_mensal;

} aluno_t;

void le_turma(aluno_t *turma, int n);
void imprime_aluno(aluno_t aluno);
bool imprime_renda(aluno_t *turma, int semestre, int n);
bool imprime_semestre(aluno_t *turma, int semestre, int n);
bool imprime_idade(aluno_t *turma, int idade, int n);

int main()
{
    int n, escolha;
    float renda_media;

    printf("\nDigite o número de alunos: ");
    scanf("%i", &n);
    getchar();

    aluno_t *turma = malloc(n * sizeof(aluno_t));

    le_turma(turma, n);

    do
    {
        do
        {
            printf("Deseja imprimir:\n");
            printf("\t(1) Alunos que possuam renda mensal superior à media de seu semestre.\n");
            printf("\t(2) Alunos que estão no mesmo semestre.\n");
            printf("\t(3) Alunos que a idade escolhida.\n");
            printf("\t(4) Sair.");
            printf("\n\tDigite sua escolha: ");

            scanf("%i", &escolha);
            getchar();
            system("clear");

        } while (escolha != 1 && escolha != 2 && escolha != 3 && escolha != 4);

        switch (escolha)
        {
            int escolha_sem_1;
            int escolha_sem_2;
            int escolha_id;

            case 1:
                printf("Digite o semestre: ");
                scanf("%i", &escolha_sem_1);
                getchar();
                imprime_renda(turma, escolha_sem_1, n);
                break;

            case 2:
                printf("Digite o semestre: ");
                scanf("%i", &escolha_sem_2);
                getchar();
                imprime_semestre(turma, escolha_sem_2, n);
                break;

            case 3:
                printf("Digite a Idade: ");
                scanf("%i", &escolha_id);
                getchar();
                imprime_idade(turma, escolha_id, n);
                break;

            case 4:
                return 0;   
        }
        printf("\nPressione ENTER para continuar: ");
        getchar();
        system("clear");

    } while (escolha != 4);

    free(turma);
    
    return 0;
}


void le_turma(aluno_t *turma, int n)
{
    for(int i = 0; i < n; i++)
    {
        printf("\nDigite os dados do %iº aluno:\n", i+1);

        printf("\t-> Nome: ");
        fgets(turma[i].nome, 82, stdin);

        int tam = strlen(turma[i].nome);
        if (turma[i].nome[tam - 1] == '\n')
        {
            turma[i].nome[tam - 1] = '\0';
        }

        printf("\t-> Idade: ");
        scanf("%i", &turma[i].idade);
        getchar();

        printf("\t-> Semestre: ");
        scanf("%i", &turma[i].semestre);
        getchar();

        printf("\t-> Renda mensal: ");
        scanf("%f", &turma[i].renda_mensal);
        getchar();
    }
    system("clear");
}

bool imprime_renda(aluno_t *turma, int semestre, int n)
{
    bool sem = false;
    int k = 0;
    float media = 0.0;

    for (int i = 0; i < n; i++)
    {
        if (turma[i].semestre == semestre)
        {
            if (sem == false) sem = true;

            media += turma[i].renda_mensal;
            k++;
        }
    }

    if (sem == false)
    {
        printf("\nNenhum aluno foi encontrado no semestre escolhido.\n");
        return false;
    }

    media /= k;
    printf("\nMedia = %f\n", media);

    for (int i = 0; i < n; i++)
    {
        if (turma[i].renda_mensal >= media && turma[i].semestre == semestre)
        {
            imprime_aluno(turma[i]);
        }
    }

    return true;
}

bool imprime_semestre(aluno_t *turma, int semestre, int n)
{
    bool sem = false;

    for (int i = 0; i < n; i++)
    {
        if (turma[i].semestre == semestre)
        {
            if (sem == false) sem = true;

            imprime_aluno(turma[i]);
        }
    }

    if (sem == false)
    {
        printf("\nNenhum aluno foi encontrado no semestre escolhido.\n");
        return false;
    }

    return true;
}

bool imprime_idade(aluno_t *turma, int idade, int n)
{
    bool id = false;

    for (int i = 0; i < n; i++)
    {
        if (turma[i].idade == idade)
        {
            if (id == false) id = true;

            imprime_aluno(turma[i]);
        }
    }

    if (id == false)
    {
        printf("\nNenhum aluno com a idade escolhida foi encontrado.\n");
        return false;
    }

    return true;
}

void imprime_aluno(aluno_t aluno)
{
    printf("\nNome: %s\n", aluno.nome);
    printf("Idade: %i\n", aluno.idade);
    printf("Semestre: %i\n", aluno.semestre);
    printf("Renda mensal: %f\n", aluno.renda_mensal);
}
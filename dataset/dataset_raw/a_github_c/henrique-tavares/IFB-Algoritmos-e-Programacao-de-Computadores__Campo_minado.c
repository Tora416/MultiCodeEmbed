#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#define n 5
#define m 5
#define true 1
#define false 0

int main()
{
    char entrada[100];
    int string;
    int matriz_final[n][m];
    char matriz_entrada[n][m];
    int linha, coluna, random_bomb, menu, menu2, menu3, menu12, menu13;
    int mapa = false, instrucoes = false, creditos = false, sair = false;
    int qtd_bombas, random;
    random = (n + m) / 3;

    while (sair == false)
    {
        system("clear");
        printf("\tBem vindo ao gerador de mapa de campo minado.\n\n\t(1) Iniciar\n\t(2) Instruções\n\t(3) Créditos\n\t(4) Sair\n\t ");
        scanf("%d", &menu);
        getchar();
        system("clear");

        switch (menu)
        {
        case 1:
            mapa = true;
            while (mapa == true)
            {
                printf("\t(1) Gerador de mapa manual\n\t(2) Gerador de mapa randômico\n\t ");
                scanf("%d", &menu12);
                getchar();
                switch (menu12)
                {
                case 1:
                    system("clear");
                    for (int i = 0; i < n; i++)
                    {
                        do
                        {
                            printf("Informe as %d linhas da matriz com %d elementos válidos,\nou seja 'X' para bomba e 'L' para não bomba,\nos elementos deverão ser inseridos sem espaços entre eles.\nAo fim de uma linha, pressione 'enter' para escrever a próxima linha.\n\n", n, m);
                            for (int j = 0; j < i; j++)
                            {
                                for (int k = 0; k < m; k++)
                                {
                                    printf("%c", matriz_entrada[j][k]);
                                }
                                printf("\n");
                            }
                            setbuf(stdin, NULL);
                            scanf("%s", entrada);
                            getchar();

                            string = true;
                            if (strlen(entrada) != m)
                            {
                                string = false;
                            }
                            for (int j = 0; j < m; j++)
                            {
                                if ((toupper(entrada[j]) != 'X') && (toupper(entrada[j]) != 'L'))
                                {
                                    string = false;
                                }
                            }
                            if (string == false)
                            {
                                printf("\nstring inválida\n");
                                sleep(1);
                                system("clear");
                            }
                        } while (string == false);

                        for (int j = 0; j < m; j++)
                        {
                            matriz_entrada[i][j] = entrada[j];
                        }

                        for (int j = 0; j < m; j++)
                        {
                            if (toupper(entrada[j]) == 'X')
                            {
                                matriz_final[i][j] = 88;
                            }
                            else
                            {
                                matriz_final[i][j] = 0;
                            }
                        }
                        system("clear");
                    }

                    for (int i = 0; i < n; i++)
                    {
                        for (int j = 0; j < m; j++)
                        {
                            qtd_bombas = 0;
                            if (matriz_final[i][j] != 88)
                            {
                                if (j != 0)
                                {
                                    if (matriz_final[i][j - 1] == 88)
                                    {
                                        qtd_bombas++;
                                    }
                                }
                                if (j != (m - 1))
                                {
                                    if (matriz_final[i][j + 1] == 88)
                                    {
                                        qtd_bombas++;
                                    }
                                }
                                if (i != 0)
                                {
                                    if (matriz_final[i - 1][j] == 88)
                                    {
                                        qtd_bombas++;
                                    }
                                }
                                if (i != (n - 1))
                                {
                                    if (matriz_final[i + 1][j] == 88)
                                    {
                                        qtd_bombas++;
                                    }
                                }
                                if ((j != (m - 1)) && (i != (n - 1)))
                                {
                                    if (matriz_final[i + 1][j + 1] == 88)
                                    {
                                        qtd_bombas++;
                                    }
                                }
                                if ((j != 0) && (i != (n - 1)))
                                {
                                    if (matriz_final[i + 1][j - 1] == 88)
                                    {
                                        qtd_bombas++;
                                    }
                                }
                                if ((j != 0) && (i != 0))
                                {
                                    if (matriz_final[i - 1][j - 1] == 88)
                                    {
                                        qtd_bombas++;
                                    }
                                }
                                if ((j != (m - 1)) && (i != 0))
                                {
                                    if (matriz_final[i - 1][j + 1] == 88)
                                    {
                                        qtd_bombas++;
                                    }
                                }
                                matriz_final[i][j] = qtd_bombas;
                            }
                        }
                    }

                    while (mapa == true)
                    {
                        linha = 0;
                        coluna = 0;
                        printf("colunas:      ");
                        for (int j = 0; j < m; j++)
                        {
                            printf("%-2i", coluna);
                            coluna++;
                            printf("  ");
                        }
                        printf("\n\t      ");
                        for (int j = 0; j < m; j++)
                        {
                            printf("|   ");
                        }
                        printf("\n\n");
                        for (int i = 0; i < n; i++)
                        {
                            for (int j = 0; j < m; j++)
                            {
                                if (j == 0)
                                {
                                    printf("linha: %2i --  ", linha);
                                    linha++;
                                }
                                if (matriz_final[i][j] == 88)
                                {
                                    printf("%c   ", matriz_final[i][j]);
                                }
                                else
                                {
                                    printf("%d   ", matriz_final[i][j]);
                                }
                            }
                            printf("\n\n");
                        }

                        printf("\tQuando estiver pronto digite '0' para voltar: ");
                        scanf("%d", &menu13);
                        getchar();
                        if (menu13 == 0)
                        {
                            mapa = false;
                        }
                        else
                        {
                            system("clear");
                        }
                    }
                    break;

                case 2:
                    system("clear");
                    srand(time(NULL));
                    for (int i = 0; i < n; i++)
                    {
                        for (int j = 0; j < m; j++)
                        {
                            random_bomb = rand() % random;
                            if (random_bomb == 0)
                            {
                                matriz_final[i][j] = 88;
                            }
                            else
                            {
                                matriz_final[i][j] = 0;
                            }
                        }
                    }

                    for (int i = 0; i < n; i++)
                    {
                        for (int j = 0; j < m; j++)
                        {
                            qtd_bombas = 0;
                            if (matriz_final[i][j] != 88)
                            {
                                if (j != 0)
                                {
                                    if (matriz_final[i][j - 1] == 88)
                                    {
                                        qtd_bombas++;
                                    }
                                }
                                if (j != (m - 1))
                                {
                                    if (matriz_final[i][j + 1] == 88)
                                    {
                                        qtd_bombas++;
                                    }
                                }
                                if (i != 0)
                                {
                                    if (matriz_final[i - 1][j] == 88)
                                    {
                                        qtd_bombas++;
                                    }
                                }
                                if (i != (n - 1))
                                {
                                    if (matriz_final[i + 1][j] == 88)
                                    {
                                        qtd_bombas++;
                                    }
                                }
                                if ((j != (m - 1)) && (i != (n - 1)))
                                {
                                    if (matriz_final[i + 1][j + 1] == 88)
                                    {
                                        qtd_bombas++;
                                    }
                                }
                                if ((j != 0) && (i != (n - 1)))
                                {
                                    if (matriz_final[i + 1][j - 1] == 88)
                                    {
                                        qtd_bombas++;
                                    }
                                }
                                if ((j != 0) && (i != 0))
                                {
                                    if (matriz_final[i - 1][j - 1] == 88)
                                    {
                                        qtd_bombas++;
                                    }
                                }
                                if ((j != (m - 1)) && (i != 0))
                                {
                                    if (matriz_final[i - 1][j + 1] == 88)
                                    {
                                        qtd_bombas++;
                                    }
                                }
                                matriz_final[i][j] = qtd_bombas;
                            }
                        }
                    }

                    while (mapa == true)
                    {
                        linha = 0;
                        coluna = 0;
                        printf("colunas:      ");
                        for (int j = 0; j < m; j++)
                        {
                            printf("%-2i", coluna);
                            coluna++;
                            printf("  ");
                        }
                        printf("\n\t      ");
                        for (int j = 0; j < m; j++)
                        {
                            printf("|   ");
                        }
                        printf("\n\n");
                        for (int i = 0; i < n; i++)
                        {
                            for (int j = 0; j < m; j++)
                            {
                                if (j == 0)
                                {
                                    printf("linha: %2i --  ", linha);
                                    linha++;
                                }
                                if (matriz_final[i][j] == 88)
                                {
                                    printf("%c   ", matriz_final[i][j]);
                                }
                                else
                                {
                                    printf("%d   ", matriz_final[i][j]);
                                }
                            }
                            printf("\n\n");
                        }

                        printf("\tQuando estiver pronto digite '0' para voltar: ");
                        scanf("%d", &menu13);
                        getchar();
                        if (menu13 == 0)
                        {
                            mapa = false;
                        }
                        else
                        {
                            system("clear");
                        }
                    }
                    break;

                default:
                    system("clear");
                    break;
                }
            }
            break;

        case 2:
            instrucoes = true;
            while (instrucoes == true)
            {
                printf("\tA matriz por padrão tem tamanho 5x5, porém é possível mudar o tamanho da matriz,\n");
                printf("\talterando no inicio código os valores de n (linhas) e m (colunas) no #define. Ex: '#define n 7'\n\n");
                printf("\tGeração manual:\n\n");
                printf("\tPara cada linha da matriz deverá ser digitado uma string (sem espaços) do tamanho do número de colunas,\n");
                printf("\tEssa string deverá conter apenas 'X' para indicar uma bomba e 'L' para indicar não-bomba.\n");
                printf("\tApós digitada a linha, deverá pressionar 'enter', para poder escrever a próxima linha.\n\n");
                printf("\tGeração randômica:\n\n");
                printf("\tCaso deseja alterar a chance de que ocorra uma bomba, basta alterar a variável: 'random',\n");
                printf("\tComo a ocorrência de bomba é determinada pela escolha aleatória de um número de 0 até o random,\n");
                printf("\tQuanto maior for o random menor a chance de aparecer uma bomba.\n\n");
                printf("\tQuando estiver pronto digite '0' para voltar: ");
                scanf("%d", &menu2);
                getchar();
                if (menu2 == 0)
                {
                    instrucoes = false;
                }
                else
                {
                    system("clear");
                }
            }
            break;

        case 3:
            creditos = true;
            while (creditos == true)
            {
                printf("\tEste trabalho, o gerador de mapa de campo minado, foi feito por:\n\n");
                printf("\tDarla Ellen Santos Garcez\n\tGustavo Cunha Lacerda\n\tHenrique Tavares Aguiar\n\n");
                printf("\tQuando estiver pronto, digite '0' para voltar: ");
                scanf("%d", &menu3);
                getchar();
                if (menu3 == 0)
                {
                    creditos = false;
                }
                else
                {
                    system("clear");
                }
            }
            break;

        case 4:
            sair = true;
            break;
        }
    }
    return 0;
}
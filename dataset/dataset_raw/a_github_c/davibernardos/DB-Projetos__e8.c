#include <stdio.h>
#include <stdlib.h>
#include <time.h>



int main(int argc, char *argv[]) {
    char opcaoMenu;
    char opcaoJogarNovamnt;
    char opcaoJogador1;
    char opcaoJogador2;
    int opcaoJogador3;
    int opcaoComputador;
    char nomeJogador1[15];
    char nomeJogador2[15];
    char nomeJogador3[15];
    char nomeComputador[15];
    int empates = 0;
    float vitoriasJogador1 = 0;
    float vitoriasJogador2 = 0;
    float vitoriasJogador3 = 0;
    float vitoriasComputador = 0;
    float percentVitJog1;
    float percentVitJog2;
    float percentVitJog3;
    float percentVitComp;
    int totalPartidas = 0;
    
    system ("COLOR 0F");
    system ("cls");
    printf ("Bem vindo ao jogo JOKENPO!");
    printf ("\n\nDigite 1 para o modo Humano X Humano.");
    printf ("\nDigite 2 para o modo Humano X Computador.");
    printf ("\nDigite 3 para sair do jogo.");
    printf ("\n\nEscolha o modo de jogar: ");
    opcaoMenu = getch();
    switch (opcaoMenu)
        {
        case '1':
            system("cls");
            system ("COLOR 0E");
            printf ("Jogo Jokenpo: Modo Humano X Humano.");
            printf ("\n\nJogador 1 - Digite seu nome: ");
            scanf ("%s", &nomeJogador1);
            printf ("\nJogador 2 - Digite seu nome: ");
            scanf ("%s", &nomeJogador2);
            do
            {
                system("cls");
                printf ("Jogo Jokenpo - Modo Humano X Humano.");
                printf ("\n\nDigite 1 para PEDRA.");
                printf ("\nDigite 2 para PAPEL.");
                printf ("\nDigite 3 para TESOURA.");
                printf ("\n\n%s - Escolha o que vai jogar: ", nomeJogador1);
                opcaoJogador1 = getch();
                printf ("\n\n%s - Escolha o que vai jogar: ", nomeJogador2);
                opcaoJogador2 = getch();
                if (opcaoJogador1 == opcaoJogador2)
                {
                    printf ("\n\n%s e %s, voces EMPATARAM!", nomeJogador1,nomeJogador2);
                    empates++;
                }else
                {
                    if (opcaoJogador1 == '1' && opcaoJogador2 == '3')
                    {
                        printf ("\n\nVitoria %s! Pedra quebra a tesoura.", nomeJogador1);
                        vitoriasJogador1++;                         
                    }else
                    {
                        if (opcaoJogador1 == '2' && opcaoJogador2 == '1')
                        {
                            printf ("\n\nVitoria %s! Papel embrulha a pedra.", nomeJogador1);
                            vitoriasJogador1++; 
                        }else
                        {
                            if (opcaoJogador1 == '3' && opcaoJogador2 == '2')
                            {
                                printf ("\n\nVitoria %s! Tesoura corta o papel.", nomeJogador1);
                                vitoriasJogador1++;
                            }else
                            {
                                if (opcaoJogador1 == '1' && opcaoJogador2 == '2')
                                {
                                    printf ("\n\nVitoria %s! Papel embrulha a pedra.", nomeJogador2);
                                    vitoriasJogador2++;
                                }else
                                {
                                    if (opcaoJogador1 == '2' && opcaoJogador2 == '3')
                                    {
                                        printf ("\n\nVitoria %s! Tesoura corta o papel.", nomeJogador2);
                                        vitoriasJogador2++;
                                    }else
                                    {
                                        printf ("\n\nVitoria %s! Pedra quebra a tesoura.", nomeJogador2);
                                        vitoriasJogador2++;
                                    }
                                }
                            }
                        }
                    }
                }   
                sleep(2);
                totalPartidas++;
                printf ("\n\n\nDeseja jogar novamente? S/N");
                opcaoJogarNovamnt = getch();
            }
            while (opcaoJogarNovamnt == 's');
            break;
        case '2':
            system ("COLOR 0A");
            system("cls");
            printf ("Jogo Jokenpo - Modo Humano X Computador.");
            printf ("\n\nJogador - Digite seu nome: ");
            scanf ("%s", &nomeJogador3);
            printf ("\n%s - Digite um nome para o computador: ",nomeJogador3);
            scanf ("%s", &nomeComputador);
            do
            {
                system("cls");
                printf ("Jogo Jokenpo - Modo Humano X Computador.");
                printf ("\n\nDigite 1 para PEDRA.");
                printf ("\nDigite 2 para PAPEL.");
                printf ("\nDigite 3 para TESOURA.");
                printf ("\n\n%s - Escolha o que vai jogar: ", nomeJogador3);
                scanf ("%d", &opcaoJogador3);
                printf ("\n%s: Escolha o que vai jogar:", nomeComputador);
                sleep (2);
                srand((unsigned)time(NULL));
                opcaoComputador = (rand() % 3 + 1);
                if (opcaoJogador3 == opcaoComputador)
                {
                    printf ("\n\n%s e %s, voces EMPATARAM!", nomeJogador3,nomeComputador);
                    empates++;
                }else
                {
                    if (opcaoJogador3 == 1 && opcaoComputador == 3)
                    {
                        printf ("\n\nVitoria %s! Pedra quebra a tesoura.", nomeJogador3);
                        vitoriasJogador3++;                         
                    }else
                    {
                        if (opcaoJogador3 == 2 && opcaoComputador == 1)
                        {
                            printf ("\n\nVitoria %s! Papel embrulha a pedra.", nomeJogador3);
                            vitoriasJogador3++; 
                        }else
                        {
                            if (opcaoJogador3 == 3 && opcaoComputador == 2)
                            {
                                printf ("\n\nVitoria %s! Tesoura corta o papel.", nomeJogador3);
                                vitoriasJogador3++;
                            }else
                            {
                                if (opcaoJogador3 == 1 && opcaoComputador == 2)
                                {
                                printf ("\n\nVitoria %s! Papel embrulha a pedra.", nomeComputador);
                                vitoriasComputador++;
                                }else
                                {
                                    if (opcaoJogador3 == 2 && opcaoComputador == 3)
                                    {
                                        printf ("\n\nVitoria %s! Tesoura corta o papel.", nomeComputador);
                                        vitoriasComputador++;
                                    }else
                                    {
                                        printf ("\n\nVitoria %s! Pedra quebra a tesoura.", nomeComputador);
                                        vitoriasComputador++;
                                    }
                                }
                            }
                        }
                    }
                }
                sleep (2);
                totalPartidas++;
                printf ("\n\n\nDeseja jogar novamente? S/N");
                opcaoJogarNovamnt = getch();
            }
            while (opcaoJogarNovamnt == 's');
            break;
        case '3':
            system ("COLOR 0F");
            printf ("\n\nSaindo do jogo...");
            return 0;
        default:
            system ("COLOR 0F");
            printf ("\n\nOpcao invalida. Saindo do jogo...");
            return 0;
        }
    system("cls");
    system ("COLOR 0F");
    if (totalPartidas == 1 && empates == 1)
    {
        printf ("Jogo Jokenpo. Resultados: Modo Humano X Humano.");
        printf ("\n\nTotal de partidas: %d", totalPartidas);
        printf ("\nTotal de empates: %d", empates);
        printf ("\n\nNao houve ganhador.");
    }else
    {
        if (opcaoMenu == '1')
        {
            printf ("Jogo Jokenpo. Resultados: Modo Humano X Humano.");
            printf ("\n\nTotal de partidas: %d", totalPartidas);            printf ("\nTotal de empates: %d", empates);
            printf ("\n\n%s:\nPercentual de vitorias: %.1f", nomeJogador1,percentVitJog1 = (vitoriasJogador1 / (totalPartidas - empates)) * 100);
            printf ("\n\n%s:\nPercentual de vitorias: %.1f\n\n", nomeJogador2,percentVitJog2 = (vitoriasJogador2 / (totalPartidas - empates)) * 100);   
        }
        else
        {
            if (opcaoMenu == '2')
            printf ("Jogo Jokenpo. Resultados: Modo Humano X Computador.");
            printf ("\n\nTotal de partidas: %d", totalPartidas);
            printf ("\nTotal de empates: %d", empates);
            printf ("\n\n%s:\nPercentual de vitorias: %.1f", nomeJogador3,percentVitJog3 = (vitoriasJogador3 / (totalPartidas - empates)) * 100);
            printf ("\n\n%s:\nPercentual de vitorias: %.1f\n\n", nomeComputador,percentVitComp = (vitoriasComputador / (totalPartidas - empates)) * 100);
        }
    }
return 0;
}

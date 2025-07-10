#include <stdio.h>
#include <stdlib.h>



int main(int argc, char *argv[]) {
    float percVitoriasComputador, percVitoriasJogador, percVitoriasJogador1, percVitoriasJogador2;
    int computador, jogador, jogador1, jogador2, opcao, jogar;
    int vitComputador, vitJogador, vitJogador1, vitJogador2, empate, partidas;
    srand(time(NULL));
    
    vitComputador = 0;
    vitJogador = 0;
    vitJogador1 = 0;
    vitJogador2 = 0;
    empate = 0;
    partidas = 0;
    
    printf("\nDigite 1 para jogar contra o computador. \n");
    printf("Digite 2 para jogar contra outro jogador. \n");
    scanf("%d", &opcao);
    while(opcao < 1 || opcao > 2)
    {
        printf("Opcao invalida. Digite novamente.");
        printf("\nDigite 1 para jogar contra o computador. \n");
        printf("Digite 2 para jogar contra outro jogador. \n");
        scanf("%d", &opcao);
    }
        do{
            switch(opcao)
            {
                case 1:
                    printf("\nEscolha uma opcao: \n");
                    printf("1. Pedra\n");
                    printf("2. Papel\n");
                    printf("3. Tesoura\n");
                    scanf("%d", &jogador);
                    
                    while(jogador < 1 || jogador > 3)
                    {
                        printf("Opcao invalida. Digite novamente.\n");
                        printf("\nEscolha uma opcao: \n");
                        printf("1. Pedra\n");
                        printf("2. Papel\n");
                        printf("3. Tesoura\n");
                        scanf("%d", &jogador);
                    }
                    computador = rand();
                    printf("", computador, (1 + computador % 3));
                    printf("\nComputador escolheu %d\n", (1 + computador % 3));
                    if((1 + computador % 3) == 2 && jogador == 1 || (1 + computador % 3) == 3 && jogador == 2 || (1 + computador % 3) == 1 && jogador == 3)
                    {
                        printf("Computador ganhou.\n");
                        vitComputador++;
                    }else
                    {
                        if(jogador == (1 + computador % 3))
                        {
                            printf("Empate.\n");
                            empate++;
                        }else
                        {
                            printf("Jogador ganhou.\n");
                            vitJogador++;
                        }
                    }
                    partidas++;
                    printf("\nJogar novamente?\n");
                    printf("1. Sim\n");
                    printf("2. Nao\n");
                    scanf("%d", &jogar);
                    while(jogar < 1 || jogar > 2)
                    {
                        printf("Opcao invalida. Escolha novamente.\n");
                        printf("\nJogar novamente?\n");
                        printf("1. Sim\n");
                        printf("2. Nao\n");
                        scanf("%d", &jogar);
                    }
                    break;
                case 2:
                    printf("\nJogador 1 escolha uma opcao: \n");
                    printf("1. Pedra\n");
                    printf("2. Papel\n");
                    printf("3. Tesoura\n");
                    scanf("%d", &jogador1);
                    
                    while(jogador1 < 1 || jogador1 > 3)
                    {
                        printf("Opcao invalida. Digite novamente.\n");
                        printf("\nJogador 1 escolha uma opcao: \n");
                        printf("1. Pedra\n");
                        printf("2. Papel\n");
                        printf("3. Tesoura\n");
                        scanf("%d", &jogador1);
                    }
                    printf("\nJogador 2 escolha uma opcao: \n");
                    printf("1. Pedra\n");
                    printf("2. Papel\n");
                    printf("3. Tesoura\n");
                    scanf("%d", &jogador2);
                    
                    while(jogador2 < 1 || jogador2 > 3)
                    {
                        printf("Opcao invalida. Digite novamente.\n");
                        printf("\nJogador 2 escolha uma opcao: \n");
                        printf("1. Pedra\n");
                        printf("2. Papel\n");
                        printf("3. Tesoura\n");
                        scanf("%d", &jogador2);
                    }
                    if(jogador1 == 2 && jogador2 == 1 || jogador1 == 3 && jogador2 == 2 || jogador1 == 1 && jogador2 == 3)
                    {
                        printf("Jogador 1 ganhou.\n");
                        vitJogador1++;
                    }else
                    {
                        if(jogador1 == jogador2)
                        {
                            printf("Empate.\n");
                            empate++;
                        }else
                        {
                            printf("Jogador 2 ganhou.\n");
                            vitJogador2++;
                        }
                    }
                    partidas++;
                    printf("\nJogar novamente?\n");
                    printf("3. Sim\n");
                    printf("4. Nao\n");
                    scanf("%d", &jogar);
                    while(jogar < 3 || jogar > 4)
                    {
                        printf("Opcao invalida. Escolha novamente.\n");
                        printf("\nJogar novamente?\n");
                        printf("3. Sim\n");
                        printf("4. Nao\n");
                        scanf("%d", &jogar);
                    }
                    break;
            }
            if(jogar == 1)
            {
            }else
            {
                if(jogar == 2)
                {
                    printf("\nTotal de %d partida(s).\n", partidas);
                    printf("\nComputador venceu %d partida(s). \n", vitComputador);
                    printf("Jogador venceu %d partida(s). \n", vitJogador);
                    printf("Total de %d empate(s). \n", empate);
                    percVitoriasComputador = (vitComputador * 100) / partidas;
                    printf("Percentual de vitorias do computador = %.2f%%\n", percVitoriasComputador);
                    percVitoriasJogador = (vitJogador * 100) / partidas;
                    printf("Percentual de vitorias do jogador = %.2f%%\n", percVitoriasJogador);
                    break;          
                }else
                {
                    if(jogar == 3)
                    {
                    }else
                    {
                        if(jogar == 4)
                        {
                            printf("\nTotal de %d partida(s).\n", partidas);
                            printf("\nJogador 1 venceu %d partida(s). \n", vitJogador1);
                            printf("Jogador 2 venceu %d partida(s). \n", vitJogador2);
                            printf("Total de %d empate(s). \n", empate);
                            percVitoriasJogador1 = (vitJogador1 * 100) / partidas;
                            printf("Percentual de vitorias do jogador 1 = %.2f%\n", percVitoriasJogador1);
                            percVitoriasJogador2 = (vitJogador2 * 100) / partidas;
                            printf("Percentual de vitorias do jogador 2 = %.2f%\n", percVitoriasJogador2);
                            break;
                        }
                    }
                }
            }       
        }while(opcao == 1 || opcao == 2);   
    return 0;
}

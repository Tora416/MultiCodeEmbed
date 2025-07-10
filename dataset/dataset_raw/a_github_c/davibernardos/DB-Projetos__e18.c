#include <stdio.h>
#include <stdlib.h>

#define PEDRA 1
#define PAPEL 2
#define TESOURA 3
#define LAGARTO 4
#define SPOCK 5

int main(int argc, char *argv[]) {
    
    int player1, player2, optP1, optP2;
    int mainMenu, playerMenu, modeMenu, novojogo;
    int totalJogadas, empates, vitoriasP1, vitoriasP2, totalNormal, totalMelhor, totalStartrek, totalDeath, tempVitP1, tempVitP2, especial, tempDeath;
    float percentP1, percentP2;
    
    srand( time(NULL) );
    totalJogadas=0;
    totalNormal=0;
    totalMelhor=0;
    totalStartrek=0;
    totalDeath=0;
    empates=0;
    vitoriasP1=0;
    vitoriasP2=0;
    especial=3;
    
    do {
    
        system("cls");
        printf("\n     ___ _______ ___   _ _______ __    _ _______ _______ \n    |   |       |   | | |       |  |  | |       |       |\n    |   |   _   |   |_| |    ___|   |_| |    _  |   _   |\n    |   |  | |  |      _|   |___|       |   |_| |  | |  |\n ___|   |  |_|  |     |_|    ___|  _    |    ___|  |_|  |\n|       |       |    _  |   |___| | |   |   |   |       |\n|_______|_______|___| |_|_______|_|  |__|___|   |_______|");
        
        printf("\n\n\tO que voce quer fazer?\n");
        printf("\t1 - Jogar\n");
        printf("\t2 - Ver Regras\n");
        printf("\t3 - Ver Estatisticas\n");
        printf("\t4 - Sair\n\t");
        
        if (totalJogadas > especial ) {
            printf("\n\t0 - ESPECIAL DEATHMATCH\n");
        }
        
        scanf("%d",&mainMenu);
        
        while( (mainMenu>4) || (totalJogadas<especial && mainMenu<1) ){
            printf("\t-> Opcao invalida!\n");
            printf("\tO que voce quer fazer?\n\t");
            scanf("%d",&mainMenu);
        }
        
        system("cls");
        
        if (mainMenu==1){
                
                printf("\n     ___ _______ ___   _ _______ __    _ _______ _______ \n    |   |       |   | | |       |  |  | |       |       |\n    |   |   _   |   |_| |    ___|   |_| |    _  |   _   |\n    |   |  | |  |      _|   |___|       |   |_| |  | |  |\n ___|   |  |_|  |     |_|    ___|  _    |    ___|  |_|  |\n|       |       |    _  |   |___| | |   |   |   |       |\n|_______|_______|___| |_|_______|_|  |__|___|   |_______|");
                printf("\n\n\tComo voce quer jogar?\n");
                printf("\t1 - Player VS Player");
                printf("\n\t2 - Player VS Computador\n\t");
                scanf("%d",&playerMenu);
                
                while(playerMenu<1 || playerMenu>2){
                    printf("\t-> Opcao invalida!\n");
                    printf("\tComo voce quer jogar?\n\t");
                    scanf("%d",&playerMenu);
                }
                
                system("cls");
                
                printf("\n     ___ _______ ___   _ _______ __    _ _______ _______ \n    |   |       |   | | |       |  |  | |       |       |\n    |   |   _   |   |_| |    ___|   |_| |    _  |   _   |\n    |   |  | |  |      _|   |___|       |   |_| |  | |  |\n ___|   |  |_|  |     |_|    ___|  _    |    ___|  |_|  |\n|       |       |    _  |   |___| | |   |   |   |       |\n|_______|_______|___| |_|_______|_|  |__|___|   |_______|");
                printf("\n\n\tMODO DE JOGO:\n");
                printf("\t1 - Normal\n");
                printf("\t2 - Melhor de 3\n");
                printf("\t3 - Startreck\n\t");
                scanf("%d",&modeMenu);
                
                while(modeMenu<1 || modeMenu>3){
                    printf("-> Opcao invalida!\n");
                    printf("Como voce quer jogar?\n\t");
                    scanf("%d",&modeMenu);
                }
                
                system("cls");
                
                if (modeMenu==1) {
                    
                    
                    do {
                        
                        printf("Vez do Player 1.\n");
                        printf("Escolha uma opcao para jogar:\n");
                        printf("\t1 - Pedra\n");
                        printf("\t2 - Papel\n");
                        printf("\t3 - Tesoura\n");
                        printf("Numero: ");
                        scanf("%d",&optP1);
                        while( optP1<1 || optP1>3 ){
                            printf("Opcao invalida. Digite novamente: ");
                            scanf("%d",&optP1);
                        }
                        
                        system("cls");
                        
                        printf("Agora o Player 2.\n");
                        printf("Escolha uma opcao para jogar:\n");
                        printf("\t1 - Pedra\n");
                        printf("\t2 - Papel\n");
                        printf("\t3 - Tesoura\n");
                        
                        system("pause");
                        printf("Numero: ");
                        
                        if (playerMenu==1) {
                            scanf("%d",&optP2);
                            while( optP2<1 || optP2>3 ){
                                printf("Opcao invalida. Digite novamente: ");
                                scanf("%d",&optP2);
                            }
                        } else {
                            optP2 = ( rand() % 2 ) + 1;
                            printf("%d",optP2);
                        
                        }
                        
                        totalJogadas++;
                        totalNormal++;
                        
                        if (optP1==optP2) {
                            printf("\nEmpate!\n");
                            empates++;
                        } else {
                            if ( (optP1==PEDRA&&optP2==TESOURA) || (optP1==PAPEL&&optP2==PEDRA) || (optP1==TESOURA&&optP2==PAPEL) ) {
                                printf("\nPlayer 1 venceu!\n");
                                vitoriasP1++;
                            } else {
                                printf("\nPlayer 2 venceu!\n");
                                vitoriasP2++;
                            }
                        }
                        
                        printf("\nDigite 1 para jogar novamente, ou qualquer outro para sair!");
                        scanf("%d",&novojogo);
                        system("cls");
                }while(novojogo==1);
                
                }
                else {
            
                    if (modeMenu==2) {
                        
                    do {
                        
                        tempVitP1=0;
                        tempVitP2=0;
                        
                            do {
                                system("cls");
                                printf("P1(%d) VS P2 (%d)\n",tempVitP1,tempVitP2);
                            
                            printf("Vez do Player 1.\n");
                            printf("Escolha uma opcao para jogar:\n");
                            printf("\t1 - Pedra\n");
                            printf("\t2 - Papel\n");
                            printf("\t3 - Tesoura\n");
                            printf("Numero: ");
                            scanf("%d",&optP1);
                            while( optP1<1 || optP1>3 ){
                                printf("Opcao invalida. Digite novamente: ");
                                scanf("%d",&optP1);
                            }
                            
                            system("cls");
                            
                            printf("Agora o Player 2.\n");
                            printf("Escolha uma opcao para jogar:\n");
                            printf("\t1 - Pedra\n");
                            printf("\t2 - Papel\n");
                            printf("\t3 - Tesoura\n");
    
                            system("pause");
                            printf("Numero: ");
                            
                            if (playerMenu==1) {
                                scanf("%d",&optP2);
                                while( optP2<1 || optP2>3 ){
                                    printf("Opcao invalida. Digite novamente: ");
                                    scanf("%d",&optP2);
                                }
                            } else {
                                optP2 = ( rand() % 2 ) + 1;
                                printf("%d",optP2);
                            }
                            
                            if (optP1==optP2) {
                                printf("\nEmpate!\n");
                                empates++;
                            } else {
                                if ( (optP1==PEDRA&&optP2==TESOURA) || (optP1==PAPEL&&optP2==PEDRA) || (optP1==TESOURA&&optP2==PAPEL) ) {
                                    printf("\nPlayer 1 venceu a rodada!\n");
                                    tempVitP1++;
                                } else {
                                    printf("\nPlayer 2 venceu a rodada!\n");
                                    tempVitP2++;
                                }
                            }
                            system("pause");
                        
                    }while( tempVitP1<2 && tempVitP2<2 );
                        
                        totalJogadas++;
                        totalMelhor++;
                        
                        system("cls");
                        if (tempVitP1 > tempVitP2) {
                            printf("\nPlayer 1 venceu a partida!\n");
                            vitoriasP1++;
                        } else {
                            printf("\nPlayer 2 venceu a partida!\n");
                            vitoriasP2++;
                        }
                        
                        system("pause");
                        system("cls");
                        
                        printf("\nDigite 1 para jogar novamente, ou qualquer outro para sair!");
                        scanf("%d",&novojogo);
                        system("cls");
                    }while(novojogo==1);
                        
                    } else {
                        
                        if (modeMenu==3) {
                            
                            do {

                        printf("Vez do Player 1.\n");
                        printf("Escolha uma opcao para jogar:\n");
                        printf("\t1 - Pedra\n");
                        printf("\t2 - Papel\n");
                        printf("\t3 - Tesoura\n");
                        printf("\t4 - Lagarto\n");
                        printf("\t5 - Spoc\n");
                        printf("Numero: ");
                        scanf("%d",&optP1);
                        while( optP1<1 || optP1>5 ){
                            printf("Opcao invalida. Digite novamente: ");
                            scanf("%d",&optP1);
                        }
                        
                        system("cls");
                        
                        printf("Agora o Player 2.\n");
                        printf("Escolha uma opcao para jogar:\n");
                        printf("\t1 - Pedra\n");
                        printf("\t2 - Papel\n");
                        printf("\t3 - Tesoura\n");
                        printf("\t4 - Lagarto\n");
                        printf("\t5 - Spoc\n");
                        
                        system("pause");
                        printf("Numero: ");
                        
                        if (playerMenu==1) {
                            scanf("%d",&optP2);
                            while( optP2<1 || optP2>5 ){
                                printf("Opcao invalida. Digite novamente: ");
                                scanf("%d",&optP2);
                            }
                        } else {
                            optP2 = ( rand() % 4 ) + 1;
                            printf("%d",optP2);
                        }
                        
                        totalJogadas++;
                        totalStartrek++;
                        
                        if (optP1==optP2) {
                            printf("\nEmpate!\n");
                            empates++;
                        } else {
                            if (
                            
                                (optP1==PEDRA&&optP2==TESOURA) ||
                                (optP1==PEDRA&&optP2==LAGARTO) ||
                                
                                (optP1==LAGARTO&&optP2==PAPEL) ||
                                (optP1==LAGARTO&&optP2==SPOCK) ||
                                
                                (optP1==SPOCK&&optP2==PEDRA) ||
                                (optP1==SPOCK&&optP2==TESOURA) ||
                                
                                (optP1==TESOURA&&optP2==LAGARTO) ||
                                (optP1==TESOURA&&optP2==PAPEL) ||
                                
                                (optP1==PAPEL&&optP2==PEDRA) ||
                                (optP1==PAPEL&&optP2==SPOCK)
                            
                            ) {
                                printf("\nPlayer 1 venceu!\n");
                                vitoriasP1++;
                            } else {
                                printf("\nPlayer 2 venceu!\n");
                                vitoriasP2++;
                            }
                        }
                        
                        printf("\nDigite 1 para jogar novamente, ou qualquer outro para sair!!");
                        scanf("%d",&novojogo);
                        system("cls");
                    }while(novojogo==1);
                            
                        }
                        
                    }
            
                }
        
        }
        
        else {
            
            if (mainMenu==2) {
                
                printf("\n     ___ _______ ___   _ _______ __    _ _______ _______ \n    |   |       |   | | |       |  |  | |       |       |\n    |   |   _   |   |_| |    ___|   |_| |    _  |   _   |\n    |   |  | |  |      _|   |___|       |   |_| |  | |  |\n ___|   |  |_|  |     |_|    ___|  _    |    ___|  |_|  |\n|       |       |    _  |   |___| | |   |   |   |       |\n|_______|_______|___| |_|_______|_|  |__|___|   |_______|");
                
                printf("\n\n\tREGRAS:\n");
                printf("\tNo Jokenpo, os jogadores devem escolher numeros, no qual cada numero representa um simbolo.\n");
                printf("\tEsses simbolos sao comparados para ver quem ganhou, da seguinte forma:\n");
                printf("\t\t- PEDRA ganha da TESOURA (quebrando-a).\n");
                printf("\t\t- TESOURA ganha do PAPEL (cortando-o).\n");
                printf("\t\t- PAPEL ganha da PEDRA (embrulhando-o).\n");
                printf("\tNa variacao Star Trek as regras anteriores permanecem, e outras sao adicionadas:\n");
                printf("\t\t- PEDRA ganha do LAGARTO (esmagando-o).\n");
                printf("\t\t- TESOURA ganha do LAGARTO (matando-o).\n");
                printf("\t\t- PAPEL ganha do SPOCK (cegando-o).\n");
                printf("\t\t- LAGARTO ganha do PAPEL (comendo-o).\n");
                printf("\t\t- LAGARTO ganha do SPOCK (envenenando-o).\n");
                printf("\t\t- SPOCK ganha da PEDRA (vaporizando-a).\n");
                printf("\t\t- SPOCK ganha da TESOURA (quebrando-a).\n\n");
                system("pause");
                
            } else {
                
                if (mainMenu==3) {
                    
                    printf("\n     ___ _______ ___   _ _______ __    _ _______ _______ \n    |   |       |   | | |       |  |  | |       |       |\n    |   |   _   |   |_| |    ___|   |_| |    _  |   _   |\n    |   |  | |  |      _|   |___|       |   |_| |  | |  |\n ___|   |  |_|  |     |_|    ___|  _    |    ___|  |_|  |\n|       |       |    _  |   |___| | |   |   |   |       |\n|_______|_______|___| |_|_______|_|  |__|___|   |_______|");
                    printf("\n\n\tTotal de Jogadas: %d\n",totalJogadas);
                    
                    printf("\t\tEmpates: %d\n",empates);
                    percentP1=(100.0*vitoriasP1)/totalJogadas;
                    printf("\t\tVitorias Player 1: %d(%f%%)\n",vitoriasP1,percentP1);
                    percentP2=(100.0*vitoriasP2)/totalJogadas;
                    printf("\t\tVitorias Player 2: %d(%f%%)\n",vitoriasP2,percentP2);

                    printf("\tJogadas no Modo Normal: %d\n",totalNormal);
                    printf("\tJogadas no Modo Melhor de 3: %d\n",totalMelhor);
                    printf("\tJogadas no Modo Star Trek: %d\n",totalStartrek);
                    system("pause");
                    
                } else if (mainMenu==0) {
                            
                    do {
                        
                        tempVitP1=0;
                        tempDeath=0;
                        
                            do {
                                
                            printf("\tDEATMATCH\n");
                            printf("\tEste e o modo especial de Jokenpo. Resista o maximo que puder e veja quantas partidas seguidas voce consegue vencer!\n");
                                
                            system("cls");
                            printf("P1(%d) VS P2 (%d)\n",tempVitP1,tempVitP2);
                            
                            printf("Vez do Player 1.\n");
                            printf("Escolha uma opcao para jogar:\n");
                            printf("\t1 - Pedra\n");
                            printf("\t2 - Papel\n");
                            printf("\t3 - Tesoura\n");
                            printf("Numero: ");
                            scanf("%d",&optP1);
                            while( optP1<1 || optP1>3 ){
                                printf("Opcao invalida. Digite novamente: ");
                                scanf("%d",&optP1);
                            }
                            
                            system("cls");
                            
                            printf("Agora o Player 2.\n");
                            printf("Escolha uma opcao para jogar:\n");
                            printf("\t1 - Pedra\n");
                            printf("\t2 - Papel\n");
                            printf("\t3 - Tesoura\n");
    
                            system("pause");
                            printf("Numero: ");

                            optP2 = ( rand() % 2 ) + 1;
                            printf("%d",optP2);
                            
                            if (optP1==optP2) {
                                printf("\nEmpate!\n");
                                empates++;
                            } else {
                                if ( (optP1==PEDRA&&optP2==TESOURA) || (optP1==PAPEL&&optP2==PEDRA) || (optP1==TESOURA&&optP2==PAPEL) ) {
                                    printf("\nPlayer 1 venceu a rodada!\n");
                                    tempVitP1=1;
                                    tempDeath++;
                                } else {
                                    printf("\nPlayer 2 venceu a rodada e encerrou a partida!\n");
                                    tempVitP1=2;
                                }
                            }
                            system("pause");
                        
                    }while( tempVitP1==1 );
                        
                        totalJogadas++;
                        totalDeath++;
                        
                        system("cls");

                            printf("\nVoce ganhou: %d partidas!\n",tempDeath);
                            vitoriasP1++;
                        
                        system("pause");
                        system("cls");
                        
                        printf("\nDigite 1 para jogar novamente, ou qualquer outro para sair!");
                        scanf("%d",&novojogo);
                        system("cls");
                    }while(novojogo==1);
                    
                }
                
            }
            
        }
    
    }while(mainMenu>=1 && mainMenu<=3);
    return 0;
}

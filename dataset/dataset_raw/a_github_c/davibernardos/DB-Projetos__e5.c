#include <stdio.h>
#include <stdlib.h>



int main(int argc, char *argv[]) {

    int modoJogo;
    int jogarNovamente;
    int jogador1;
    int jogador2;
    int ia;
    int empates;
    int vitoriasP1;
    float porcentvitP1;
    int vitoriasP2;
    float porcentvitP2;
    int vitoriasIA;
    float porcentvitIA;
    int contador;

    printf("-^^- JOKENPO GAME by TS -^^- \n \n \n");
    printf("Digite o numero de uma das opcoes abaixo:\n 1 - Jogar Player Vs Player \n 2- Jogar Player Vs IA\n 3- Sair\n");
    scanf("%d", &modoJogo);
    while(modoJogo != 1 && modoJogo !=2 && modoJogo !=3 ) {
        printf("Opcao Invalida, digite uma opcao valida:\n 1 - Jogar Player Vs Player \n 2- Jogar Player Vs IA\n 3- Sair\n");
        scanf("%d", &modoJogo);

    }
    switch (modoJogo) {
        case 1:
        printf(" -^^- MODO PLAYER VS PLAYER -^^- \n \n \n");
        jogarNovamente=1;
        vitoriasP1=0;
        vitoriasP2=0;
        contador=0;
        do {
            printf("Player 1 -> Digite sua opcao de jogada: \n 1 - PEDRA \n 2 - PAPEL \n 3 - TESOURA \n");
            scanf("%d", &jogador1);
            while(jogador1 >3) {
                printf("Jogada Invalida, por favor digite uma jogada valida:\n 1 - PEDRA \n 2 - PAPEL \n 3 - TESOURA \n");
                scanf("%d", & jogador1);
            }
            printf("Player 2 -> Digite sua opcao de jogada: \n 1 - PEDRA \n 2 - PAPEL \n 3 - TESOURA \n");
            scanf("%d", &jogador2);
            while(jogador2 >3) {
                printf("Jogada Invalida, por favor digite uma jogada valida:\n 1 - PEDRA \n 2 - PAPEL \n 3 - TESOURA \n");
                scanf("%d", & jogador2);
            }

            if((jogador1 == 1 && jogador2 == 1) || (jogador1 == 2 && jogador2 == 2)|| (jogador1==3 && jogador2==3)) {
                printf("EMPATOU! \n");
                empates++;
                contador++;

            } else {
                if(jogador1 == 1 && jogador2 == 2) {
                    printf("PEDRA E PAPEL = VITORIA JOGADOR 2! \n");
                    vitoriasP2++;
                    contador++;

                } else {
                    if(jogador1==1 && jogador2 == 3) {
                        printf("PEDRA E TESOURA = VITORIA JOGADOR 1! \n");
                        vitoriasP1++;
                        contador++;

                    } else {
                        if(jogador1==2 && jogador2==1) {
                            printf("PAPEL E PEDRA = VITORIA JOGADOR 1! \n");
                            vitoriasP1++;
                            contador++;


                        } else {
                            if(jogador1==2 && jogador2==3) {
                                printf("PAPEL E TESOURA = VITORIA JOGADOR 2! \n");
                                vitoriasP2++;
                                contador++;


                            } else {
                                if(jogador1==3 && jogador2==1) {
                                    printf("TESOURA E PEDRA = VITORIA JOGADOR 2! \n");
                                    vitoriasP2++;
                                    contador++;

                                } else {
                                    printf("TESOURA E PAPEL = VITORIA JOGADOR 1! \n");
                                    vitoriasP1++;
                                    contador++;


                                }


                            }

                        }
                    }
                }

            }
            printf("Deseja jogar Novamente? \n 1- Sim\n 2-Nao \n");
            scanf("%d", &jogarNovamente);
            while(jogarNovamente >2) {
                printf("Opcao Invalida, digite uma opcao valida:\n 1- Sim\n 2-Nao \n");
                scanf("%d", &jogarNovamente);
            }
        } while(jogarNovamente ==1);
        printf("ESTATISTICAS: \n");
        printf("Numero de Vezes Jogadas: %d \n", contador);
        printf("Numero de Empates: %d \n", empates);
        if(vitoriasP1 == 0 && vitoriasP2 == 0) {
            printf("Porcentagem de Vitorias PLAYER 1 = 0 \nPorcentagem de Vitorias PLAYER 2 = 0");
        } else {

            porcentvitP1=(vitoriasP1*100)/(contador-empates);
            porcentvitP2=(vitoriasP2*100)/(contador-empates);
            printf("Porcentagem de Vitorias PLAYER 1 = %f \n", porcentvitP1);
            printf("Porcentagem de Vitorias PLAYER 2 = %f \n", porcentvitP2);
        }
        break;
    case 2:
        printf(" -^^- MODO PLAYER VS I.A -^^- \n \n \n");
        jogarNovamente=1;
        vitoriasP1=0;
        vitoriasIA=0;
        contador=0;
        do {
            printf("Player -> Digite sua opcao de jogada: \n 1 - PEDRA \n 2 - PAPEL \n 3 - TESOURA \n");
            scanf("%d", &jogador1);
            while(jogador1 >3) {
                printf("Jogada Invalida, por favor digite uma jogada valida:\n 1 - PEDRA \n 2 - PAPEL \n 3 - TESOURA \n");
                scanf("%d", & jogador1);
            }
            srand(time(NULL));
            ia=(rand() % 3)+1;
            printf("Jogada da maquina:\n %d\n", ia);

            if((jogador1 == 1 && ia == 1) || (jogador1 == 2 && ia == 2)|| (jogador1==3 && ia==3)) {
                printf("EMPATOU! \n");
                empates++;
                contador++;

            } else {
                if(jogador1 == 1 && ia == 2) {
                    printf("PEDRA E PAPEL = VITORIA MAQUINA! \n");
                    vitoriasIA++;
                    contador++;

                } else {
                    if(jogador1==1 && ia == 3) {
                        printf("PEDRA E TESOURA = VITORIA JOGADOR! \n");
                        vitoriasP1++;
                        contador++;

                    } else {
                        if(jogador1==2 && ia==1) {
                            printf("PAPEL E PEDRA = VITORIA JOGADOR! \n");
                            vitoriasP1++;
                            contador++;


                        } else {
                            if(jogador1==2 && ia==3) {
                                printf("PAPEL E TESOURA = VITORIA MAQUINA! \n");
                                vitoriasIA++;
                                contador++;


                            } else {
                                if(jogador1==3 && ia==1) {
                                    printf("TESOURA E PEDRA = VITORIA MAQUINA! \n");
                                    vitoriasIA++;
                                    contador++;

                                } else {
                                    printf("TESOURA E PAPEL = VITORIA JOGADOR! \n");
                                    vitoriasP1++;
                                    contador++;


                                }


                            }

                        }
                    }
                }

            }
            printf("Deseja jogar Novamente? \n 1- Sim\n 2-Nao \n");
            scanf("%d", &jogarNovamente);
            while(jogarNovamente >2) {
                printf("Opcao Invalida, digite uma opcao valida:\n 1- Sim\n 2-Nao \n");
                scanf("%d", &jogarNovamente);
            }
        } while(jogarNovamente ==1);
        printf("ESTATISTICAS: \n");
        printf("Numero de Vezes Jogadas: %d \n", contador);
        printf("Numero de Empates: %d \n", empates);
        if(vitoriasP1 == 0 && vitoriasIA == 0) {
            printf("Porcentagem de Vitorias PLAYER 1 = 0 \nPorcentagem de Vitorias PLAYER 2 = 0");
        } else {

            porcentvitP1=(vitoriasP1*100)/(contador-empates);
            porcentvitIA=(vitoriasIA*100)/(contador-empates);
            printf("Porcentagem de Vitorias PLAYER 1 = %f \n", porcentvitP1);
            printf("Porcentagem de Vitorias da MAQUINA = %f \n", porcentvitIA);
        }
        break;
        case 3:
            exit(0);
            break;
        }

    system("pause");
    return 0;
}

#include <stdio.h>
#include <stdlib.h>



int main(int argc, char *argv[]) {
        int pontosJogador1=0, pontosComputador=0, pontosJogador2=0;
        int jogador1, computador, jogador2;
        int numeroPartidas=0, numeroPartidasJogador2=0, numeroPartidasComputador=0, empate=0;
        int continuar=1, mododejogo;
        float percJogador1=0, percJogador2=0, percComputador=0;
        
        while(continuar == 1) {
            printf ("-------\n");
            printf ("JOKENPO\n");
            printf ("-------\n\n");
            printf ("Quem sera o seu oponente:\n"
                    "1. Computador\n"
                    "2. Jogador\n");
            scanf("%d", &mododejogo);
            printf ("\n");
            numeroPartidas++;
            switch (mododejogo)
            {
            case 1: printf ("Jogador X Computador\n\n");
                    printf ("1. Pedra\n");
                    printf ("2. Papel\n");
                    printf ("3. Tesoura\n");
                    scanf ("%d", &jogador1);
                    
                   numeroPartidasComputador++;
                   
                    srand(time(NULL));
                    computador = rand() % 3; 
                    
                    computador++;   
                        
                    switch (computador)
                    {
                        case 1: printf ("Computador --> Pedra\n");break;
                        case 2: printf ("Computador --> Papel\n");break;                        
                        case 3: printf ("Computador --> Tesoura\n");break;                  
                    }
                    
                if ((jogador1 == 1 && computador==3) || (jogador1 == 2 && computador == 1) || (jogador1 == 3 && computador == 2)) 
                {
                    printf("Voce venceu!\n\n\n");
                    pontosJogador1++;
                } else if (jogador1 == computador) 
                {
                    printf ("Empate!\n\n\n");
                    empate++;
                }
                else
                {
                    printf ("Computador venceu!\n\n\n");
                    pontosComputador++;
                }
                printf("Continuar: \n\n1.Sim\n2.Nao\n");
                scanf("%d", &continuar);
                system("cls");
            break;
            
            case 2: printf ("Jogador1 X Jogador2\n\n");
                    printf ("1. Pedra\n");
                    printf ("2. Papel\n");
                    printf ("3. Tesoura\n");
                    scanf ("%d", &jogador1);
                    scanf ("%d", &jogador2);
                    
                    numeroPartidasJogador2++;
                    switch (jogador1)
                    {
                        case 1: printf ("Jogador1 --> Pedra\n");break;
                        case 2: printf ("Jogador1 --> Papel\n");break;
                        case 3: printf ("Jogador1 --> Tesoura\n");break;
                    }
                    switch (jogador2)
                    {
                        case 1: printf ("Jogador2 --> Pedra\n");break;
                        case 2: printf ("Jogador2 --> Papel\n");break;
                        case 3: printf ("Jogador2 --> Tesoura\n");break;
                    }
                    
                    if ((jogador1 == 1 && jogador2 == 3) || (jogador1 == 2 && jogador2 == 1) || (jogador1 == 3 && jogador2 == 2)) 
                        {
                            printf("Jogador1 venceu!\n\n");
                            pontosJogador1++;
                        } else if (jogador1 == jogador2) 
                        {
                            printf ("Empate!\n\n");
                            empate ++;
                        }else
                        {
                            printf ("Jogador2 venceu!\n\n");
                            pontosJogador2++;
                        }
                printf("Continuar: \n\n1.Sim\n2.Nao\n");
                scanf("%d", &continuar);
                system("cls");
            break;
            }
        }
        percJogador1 = (pontosJogador1 * 100) / (numeroPartidas);
        percJogador1 = percJogador1;
        if(numeroPartidasJogador2 != 0)
            percJogador2 = (pontosJogador2 * 100) / (numeroPartidasJogador2);
        percComputador = (pontosComputador * 100) / (numeroPartidasComputador);
        printf("Percentual Jogador1: %f\n", percJogador1);
        printf("Percentual Computador: %f\n", percComputador);
        printf("Percentual Jogador2: %f\n", percJogador2);
        printf("Empate: %d\n", empate);
        printf("Numero Partidas: %d\n", numeroPartidas);
        printf("Pontos Jogador1: %d\n", pontosJogador1);
        printf("Pontos Jogador2: %d\n", pontosJogador2);
        printf("Pontos Computador: %d\n", pontosComputador);
        
        
        return 0;
    }

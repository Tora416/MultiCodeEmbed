#include <stdio.h>
#include <stdlib.h>



int main(int argc, char *argv[]) 
{
    int opcao, opcaoDeJogadaHumano, opcaoDeJogadaComputador, opcaoDeJogadaHumano1, opcaoDeJogadaHumano2;
    int numeroDePartidas = 0, numeroDeVitoriasHumano = 0, numeroDeVitoriasComputador = 0;
    int numeroDeVitoriasHumano1 = 0, numeroDeVitoriasHumano2 = 0, numeroDeEmpates = 0;
    
    while(1)
    {
        system("cls");
        printf("Jogo Jokenpo\n\n");
        printf("(1) humano x computador\n");
        printf("(2) humano x humano\n");
        printf("(3) resultado\n");
        printf("(4) sair\n\n");
        printf("Escolha uma das opcoes acima: ");
        scanf("%d", &opcao);
        
            
        if(opcao == 1)
        {
            numeroDePartidas++;
            printf("\n(1) = pedra\n");
            printf("(2) = papel\n");
            printf("(3) = tesoura\n");
            
            printf("\nopcao de jogada humano: ");
            scanf("%d", &opcaoDeJogadaHumano);
            
            opcaoDeJogadaComputador = rand()%3;
            printf("opcao de jogada computador: %d\n\n", opcaoDeJogadaComputador);
            
            if(opcaoDeJogadaHumano == 1 && opcaoDeJogadaComputador == 1)
            {
                printf("empate\n");
                numeroDeEmpates++;
            }
            if(opcaoDeJogadaHumano == 1 && opcaoDeJogadaComputador == 2)
            {
                printf("computador ganha\n");
                numeroDeVitoriasComputador++;
            }
            if(opcaoDeJogadaHumano == 1 && opcaoDeJogadaComputador == 3)
            {
                printf("humano ganha\n");
                numeroDeVitoriasHumano++;
            }
            if(opcaoDeJogadaHumano == 2 && opcaoDeJogadaComputador == 2)
            {
                printf("empate\n");
                numeroDeEmpates++;
            }
            if(opcaoDeJogadaHumano == 2 && opcaoDeJogadaComputador == 1)
            {
                printf("humano ganha\n");
                numeroDeVitoriasHumano++;
            }
            if(opcaoDeJogadaHumano == 2 && opcaoDeJogadaComputador == 3)
            {
                printf("computador ganha\n");
                numeroDeVitoriasComputador++;
            }
            if(opcaoDeJogadaHumano == 3 && opcaoDeJogadaComputador == 3)
            {
                printf("empate\n");
                numeroDeEmpates++;
            }
            if(opcaoDeJogadaHumano == 3 && opcaoDeJogadaComputador == 1)
            {
                printf("computador ganha\n");
                numeroDeVitoriasComputador++;
            }
            if(opcaoDeJogadaHumano == 3 && opcaoDeJogadaComputador == 2)
            {
                printf("humano ganha\n");
                numeroDeVitoriasHumano++;
            }
            system("pause");
        }
        else
        {
            if(opcao == 2)
            {
                numeroDePartidas++;
                printf("\n1 = pedra\n");
                printf("2 = papel\n");
                printf("3 = tesoura\n");
                
                printf("\nopcao de jogada humano 1: ");
                scanf("%d", &opcaoDeJogadaHumano1);
            
                printf("\nopcao de jogada humano 2: ");
                scanf("%d", &opcaoDeJogadaHumano2);
                
                if(opcaoDeJogadaHumano1 == 1 && opcaoDeJogadaHumano2 == 1)
                {
                    printf("\nempate\n");
                    numeroDeEmpates++;
                }
                if(opcaoDeJogadaHumano1 == 1 && opcaoDeJogadaHumano2 == 2)
                {
                    printf("\nhumano 2 ganha\n");
                    numeroDeVitoriasHumano2++;
                }
                if(opcaoDeJogadaHumano1 == 1 && opcaoDeJogadaHumano2 == 3)
                {
                    printf("\nhumano 1 ganha\n");
                    numeroDeVitoriasHumano1++;
                }
                if(opcaoDeJogadaHumano1 == 2 && opcaoDeJogadaHumano2 == 2)
                {
                    printf("\nempate\n");
                    numeroDeEmpates++;
                }
                if(opcaoDeJogadaHumano1 == 2 && opcaoDeJogadaHumano2 == 1)
                {
                    printf("\nhumano 1 ganha\n");
                    numeroDeVitoriasHumano1++;
                }
                if(opcaoDeJogadaHumano1 == 2 && opcaoDeJogadaHumano2 == 3)
                {
                    printf("\nhumano 2 ganha\n");
                    numeroDeVitoriasHumano2++;
                }
                if(opcaoDeJogadaHumano1 == 3 && opcaoDeJogadaHumano2 == 3)
                {
                    printf("\nempate\n");
                    numeroDeEmpates++;
                }
                if(opcaoDeJogadaHumano1 == 3 && opcaoDeJogadaHumano2 == 1)
                {
                    printf("\nhumano 2 ganha\n");
                    numeroDeVitoriasHumano2++;
                }
                if(opcaoDeJogadaHumano1 == 3 && opcaoDeJogadaHumano2 == 2)
                {
                    printf("\nhumano 1 ganha\n");
                    numeroDeVitoriasHumano1++;
                }
                system("pause");
            }
            else
            {
                if(opcao == 3)
                {
                    printf("\nNumero de partidas: %d\n", numeroDePartidas);
                    printf("Numero de vitorias humano: %d\n", numeroDeVitoriasHumano);
                    printf("Numero de vitorias computador: %d\n", numeroDeVitoriasComputador);
                    printf("Numero de vitorias humano 1: %d\n", numeroDeVitoriasHumano1);
                    printf("Numero de vitorias humano 2: %d\n", numeroDeVitoriasHumano2);
                    printf("Numero de empates: %d\n\n", numeroDeEmpates);
                    system("pause");
                }
                else
                {
                    if(opcao == 4)
                    {
                        exit(0);
                    }
                    else
                    {
                        printf("\nopcao invalida\n\n");
                    }
                    system("pause");
                }
            }
                
        }
    
    }
    
    
    
    
    
    return 0;
}

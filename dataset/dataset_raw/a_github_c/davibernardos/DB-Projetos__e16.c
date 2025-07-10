#include <stdio.h>
#include <stdlib.h>



int main(void) {
    int jogadorUm, jogadorDois, nEmpatesUm, nEmpatesDois, nDerrotasUm , nDerrotasDois;
    int opcao, menu;
    float nVitoriasUm, nVitoriasDois, pVitoriasUm, pVitoriasDois, nJogadas;
    
    opcao = 1;
    nVitoriasDois = 0;
    nDerrotasUm = 0;
    
    printf("------------------------------------\n-------------bem vindo!-------------\n------------------------------------\n\n");
        
    while(opcao != 3){
    
    printf("Selecione seu modo de jogo: \n\n");
    printf("1- PvC - Player vs Computer \n");
    printf("2- PvP - Player vs Player \n");
    printf("3- sair\n");
    fflush(stdin);
    scanf("%d", &opcao);
    
    
    
    
    switch(opcao){
    
    
        case 1: 
        
         jogadorUm = 0;
         jogadorDois = 0;
         nVitoriasUm = 0;
         nVitoriasDois = 0;
         nEmpatesUm = 0;
         nEmpatesDois = 0;
         nJogadas = 0;
         nDerrotasUm  = 0;
         nDerrotasDois = 0;
         pVitoriasUm = 0;
         pVitoriasDois = 0;
        
        while(menu !=4){
                 
        
           printf("\nSelecione sua opcao: \n");
           printf("1- Pedra\n 2- Papel \n 3- Tesoura. \n");
           scanf("%d", &jogadorUm);
           
           srand(time(NULL));
           jogadorDois = 1 + rand() %3;
           printf("\nOpcao jogadorDois = %d ", jogadorDois, (jogadorDois % 4));
           
           
if(jogadorUm == 1 && jogadorDois == 1){
            printf("\nDeu Empate!\n");
            nEmpatesUm = nEmpatesUm + 1;
            nEmpatesDois = nEmpatesDois + 1; 
            nJogadas = nJogadas + 1;
                
      }else{
          if(jogadorUm == 1 && jogadorDois == 2){  
                       printf("\nO jogador Dois ganhou\n");
                       nDerrotasUm = nDerrotasUm + 1;
                       nVitoriasDois = nVitoriasDois + 1;
                       nJogadas = nJogadas + 1;                   
                     
         }else{
              if(jogadorUm == 1 && jogadorDois == 3){
                           printf("\nO Jogador Um ganhou\n");
                           nDerrotasDois = nDerrotasDois + 1;
                           nVitoriasUm = nVitoriasUm + 1;
                           nJogadas = nJogadas + 1;
                           
                            
              }else{
                    if(jogadorUm == 2 && jogadorDois == 1){ 
                                 printf("\nO jogador Dois ganhou\n");
                                 nDerrotasUm = nDerrotasUm + 1;
                                 nVitoriasDois = nVitoriasDois + 1;
                                 nJogadas = nJogadas + 1;
                                
                           
                    }else{
                          if(jogadorUm == 2 && jogadorDois == 2){
                                       printf("\nDeu empate\n");
                                       nEmpatesUm = nEmpatesUm + 1;
                                       nEmpatesDois = nEmpatesDois + 1;
                                       nJogadas = nJogadas + 1;
                                       
                         }else{
                               if(jogadorUm == 2 && jogadorDois == 3){  
                                            printf("\nO jogador dois ganhou\n");
                                            nVitoriasDois = nVitoriasDois + 1;
                                            nDerrotasUm = nDerrotasUm + 1;
                                            nJogadas = nJogadas + 1;
                                           
                              }else{
                                    if (jogadorUm == 3 && jogadorDois == 1){
                                                  printf("\nO jogador Dois ganhou\n");
                                                  nVitoriasDois = nVitoriasDois + 1;
                                                  nDerrotasUm = nDerrotasUm + 1;
                                                  nJogadas = nJogadas + 1;
                                                  
                                                           
                                    }else{
                                          if(jogadorUm == 3 && jogadorDois == 2){
                                                       printf("\nO jogador Um ganhou\n");
                                                       nDerrotasDois = nDerrotasDois + 1;
                                                       nVitoriasUm = nVitoriasUm + 1;
                                                       nJogadas = nJogadas + 1;
                                                      
                                            }else{
                                                  if(jogadorUm == 3 && jogadorDois == 3){
                                                               printf("\nDeu Empate\n");
                                                               nEmpatesUm = nEmpatesUm + 1;
                                                               nEmpatesDois = nEmpatesDois + 1;
                                                               nJogadas = nJogadas + 1;
                                                    
                                                  }else{
                                                       printf("\nJogada Invalida\n");
                                                  } 
                                                            
}}}}}}}}
            
            if(nVitoriasUm == 0)
            {
                   pVitoriasUm = 0;
                   }else 
                   {
                          pVitoriasUm = ( nVitoriasUm/ nJogadas ) * 100;
                   }
                                if(nVitoriasDois == 0)
                                {
                                        pVitoriasDois = 0;
                                        }else
                                        {
                                                pVitoriasDois = ( nVitoriasDois / nJogadas ) * 100;
            }
            printf("\nJOGADOR 1: \n");
            printf("\nQuantidade de Vitorias: %.0f", nVitoriasUm);
            printf("\nQuantidade de Derrotas: %d", nDerrotasUm);
            printf("\nQuantidade de Empates: %d", nEmpatesUm);
            printf("\nPercentual de Vitorias: %.2f %%", pVitoriasUm );
            printf("\n------------------------------------------------------------------");
            printf("\nJOGADOR 2: \n");
            printf("\nQuantidade de Vitorias: %.0f", nVitoriasDois);
            printf("\nQuantidade de Derrotas: %d", nDerrotasDois);
            printf("\nQuantidade de Empates: %d", nEmpatesDois);
            printf("\nPercentual de Vitorias: %.2f %%", pVitoriasDois);
            printf("\n------------------------------------------------------------------");
            printf("\nGERAL: \n");
            printf("Quantidade de Jogadas Total: %.0f", nJogadas);

            printf("\ndeseja jogar novamente?\n");
            scanf("%d", &menu);
            system("cls");
    }
        break;
           
        case 2:  
        
         jogadorUm = 0;
         jogadorDois = 0;
         nVitoriasUm = 0;
         nVitoriasDois = 0;
         nEmpatesUm = 0;
         nEmpatesDois = 0;
         nJogadas = 0;
         nDerrotasUm  = 0;
         nDerrotasDois = 0;
         pVitoriasUm = 0;
         pVitoriasDois = 0;
        
        while(opcao != 3){
        
           printf("\nSelecione sua opcao: \n");
           printf("1- Pedra\n 2- Papel \n 3- Tesoura. \n");
           scanf("%d", &jogadorUm);
           
           printf("\nSelecione sua opcao: \n");
           printf("1- Pedra\n 2- Papel \n 3- Tesoura. \n");
           scanf("%d", &jogadorDois);
           system("cls");
                   
if(jogadorUm == 1 && jogadorDois == 1){
            printf("\nDeu Empate!\n");
            nEmpatesUm = nEmpatesUm + 1;
            nEmpatesDois = nEmpatesDois + 1; 
            nJogadas = nJogadas + 1;
                
      }else{
          if(jogadorUm == 1 && jogadorDois == 2){  
                       printf("\nO jogador Dois ganhou\n");
                       nDerrotasUm = nDerrotasUm + 1;
                       nVitoriasDois = nVitoriasDois + 1;
                       nJogadas = nJogadas + 1;                   
                     
         }else{
              if(jogadorUm == 1 && jogadorDois == 3){
                           printf("\nO Jogador Um ganhou\n");
                           nDerrotasDois = nDerrotasDois + 1;
                           nVitoriasUm = nVitoriasUm + 1;
                           nJogadas = nJogadas + 1;
                           
                            
              }else{
                    if(jogadorUm == 2 && jogadorDois == 1){ 
                                 printf("\nO jogador Dois ganhou\n");
                                 nDerrotasUm = nDerrotasUm + 1;
                                 nVitoriasDois = nVitoriasDois + 1;
                                 nJogadas = nJogadas + 1;
                                
                           
                    }else{
                          if(jogadorUm == 2 && jogadorDois == 2){
                                       printf("\nDeu empate\n");
                                       nEmpatesUm = nEmpatesUm + 1;
                                       nEmpatesDois = nEmpatesDois + 1;
                                       nJogadas = nJogadas + 1;
                                       
                         }else{
                               if(jogadorUm == 2 && jogadorDois == 3){  
                                            printf("\nO jogador dois ganhou\n");
                                            nVitoriasDois = nVitoriasDois + 1;
                                            nDerrotasUm = nDerrotasUm + 1;
                                            nJogadas = nJogadas + 1;
                                           
                              }else{
                                    if (jogadorUm == 3 && jogadorDois == 1){
                                                  printf("\nO jogador Dois ganhou\n");
                                                  nVitoriasDois = nVitoriasDois + 1;
                                                  nDerrotasUm = nDerrotasUm + 1;
                                                  nJogadas = nJogadas + 1;
                                                  
                                                           
                                    }else{
                                          if(jogadorUm == 3 && jogadorDois == 2){
                                                       printf("\nO jogador Um ganhou\n");
                                                       nDerrotasDois = nDerrotasDois + 1;
                                                       nVitoriasUm = nVitoriasUm + 1;
                                                       nJogadas = nJogadas + 1;
                                                      
                                            }else{
                                                  if(jogadorUm == 3 && jogadorDois == 3){
                                                               printf("\nDeu Empate\n");
                                                               nEmpatesUm = nEmpatesUm + 1;
                                                               nEmpatesDois = nEmpatesDois + 1;
                                                               nJogadas = nJogadas + 1;
                                                    
                                                        }else{
                                                                 printf("\nJogada Invalida\n");
           
                                                                                        
}}}}}}}}}
            
            if(nVitoriasUm == 0)
            {
                   pVitoriasUm = 0;
                 }
                 else
                     {
                        pVitoriasUm = ( nVitoriasUm / nJogadas ) * 100;
                     }
                             if(nVitoriasDois == 0){
                                    pVitoriasDois = 0;
                                    }
                                     else
                                     {
                                               pVitoriasDois = ( nVitoriasDois / nJogadas ) * 100;
            }
            
            printf("\nJOGADOR 1: \n");
            printf("\nQuantidade de Vitorias: %.0f", nVitoriasUm);
            printf("\nQuantidade de Derrotas: %d", nDerrotasUm);
            printf("\nQuantidade de Empates: %d", nEmpatesUm);
            printf("\nPercentual de Vitorias: %.2f", pVitoriasUm );
            printf("\n------------------------------------------------------------------");
            printf("\nJOGADOR 2: \n");
            printf("\nQuantidade de Vitorias: %.0f", nVitoriasDois);
            printf("\nQuantidade de Derrotas: %d", nDerrotasDois);
            printf("\nQuantidade de Empates: %d", nEmpatesDois);
            printf("\nPercentual de Vitorias: %.2f %%", pVitoriasDois);
            printf("\n------------------------------------------------------------------");
            printf("\nGERAL: \n");
            printf("Quantidade de Jogadas Total: %.0f", nJogadas);
            
                
            printf("\ndeseja jogar novamente?\n");
            scanf("%d", &menu);
            system("cls");      
        }

           break;
        case 3:
           printf("Cansou de jogar? \n");
           system("exit");
           
           break;
           
        default:           
            printf("opcao invalida");
            break;
        }
}

    
    if(menu == 2){
        
        printf("Voce saira do jogo!");
    }

}



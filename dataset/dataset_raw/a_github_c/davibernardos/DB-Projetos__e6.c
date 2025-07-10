#include <stdio.h>
#include <stdlib.h>



int main(int argc, char *argv[]) 
{
    int modoJogo, jogada1, jogada2, partidas, empates, vencimento1, vencimento2, jogarNovamente, aleatorio, totalPartidas; 
    float vitorias1, vitorias2;
    
    empates=0;
    partidas=0;
    vencimento1=0;
    vencimento2=0;
    jogarNovamente=1; 
    
    printf ("*************************\n | Vamos Jogar Jokempo!| \n*************************\n \nPara iniciar, escolha o modo de jogo: \n 1- Para Jogar com outra pessoa \n 2- Para jogar com o computador \n ");
    scanf ("%d" , &modoJogo);
    
    while (modoJogo<1 || modoJogo>2)
                {
                    printf("Modo de Jogo Invalido! Tente novamnete:");
                    scanf("%d" , &modoJogo);
                }
                
    switch (modoJogo)
    {
        
        case 1 :   
            
            printf ("\n Modo de Jogo 1 \n");
            
            while ( jogarNovamente == 1)
            {
                
                 printf ("\n \n  Escolhas: \n 1- Para Pedra \n 2- Para Papel \n 3- Para Tesoura \n ");
              
                 printf ("\n \n Vez do Jogador 1:");
                 scanf ("%d" , &jogada1);
                 
                    while (jogada1>3 || jogada1<1)
                {
                    printf("Opcao Invalida! Tente novamnete:");
                    scanf("%d" , &jogada1);
                }
                
                 printf ("\n \n Vez do Jogador 2:");
                 scanf ("%d" , &jogada2);
                 
                 while (jogada2>3 || jogada2<1)
                {
                    printf("Opcao Invalida! Tente novamnete:");
                    scanf("%d" , &jogada2);
                }
                 
                    if ( jogada1 == 1 && jogada2 == 2 )
                    {
                       printf("\n RESULTADO: Papel ganha da pedra, Ganhador: Jogador 2");
                       partidas++;
                       vencimento2++;
                       
                    }else{
                        
                        if ( jogada1 == 2 && jogada2 == 1 )
                        {
                       printf("\n RESULTADO: Papel ganha da pedra, Ganhador: Jogador 1");
                       partidas++; 
                       vencimento1++;           
                       
                        }else{
                            
                            if ( jogada1 == 1 && jogada2 == 3 )
                            {
                             printf("\n RESULTADO: Pedra ganha da tesoura, Ganhador: Jogador 1");
                             partidas++;
                             vencimento1++;
                             
                            }else{
                                
                                if ( jogada1 == 3 && jogada2 == 1 )
                                
                                {
                                 printf("\n RESULTADO: Pedra ganha da tesoura, Ganhador: Jogador 2");
                                 partidas++;
                                 vencimento2++;
                                 
                                }else{
                                    
                                    if ( jogada1 == 3 && jogada2 == 2)
                                    {
                                     printf (" \n RESULTADO: Tesoura ganha do papel, Gahador: Jogador 1");
                                     partidas++;
                                     vencimento1++;
                                        
                                    }else{
                                        
                                        if ( jogada1 == 2 && jogada2 == 3 )
                                        {
                                         printf("\n RESULTADO: Tesoura ganha do papel, Ganhador: Jogador 2");
                                         partidas++;
                                         vencimento2++;
                                            
                                        }else{
                                            
                                            printf ("\n Houve Empate!");
                                            empates++;
                                            
                                            
                                            }
                                        
                                        }
                                     }
                                }
                            }
                        }
                        
                printf("\n \n Para jogar novamente digite = 1 ou sair digite = 2 : ");
                scanf("%d" , &jogarNovamente );
                
                while (jogarNovamente<1 || jogarNovamente>2)
                {
                    printf("Opcao Invalida! Tente novamnete:");
                    scanf("%d" , &jogarNovamente);
                }
                
            } 
            
        totalPartidas=partidas+empates;
        vitorias1=(100*vencimento1)/partidas;
        vitorias2=(100*vencimento2)/partidas;
    
        printf(" \n ==============\n |ESTATISTICAS| \n ==============\n Quantidade de Partidas: %d | Quantidade de Empates: %d" , totalPartidas , empates) ;
        printf("\n Percentual de Vitotias Jogador 1: %f  \n Percentual de Votorias Jogador 2: %f " , vitorias1 , vitorias2);
    
                      
                        
                 break;
        
     
            
        case 2 : 
          
          printf ("\n Modo de Jogo 2 \n");
            
            while ( jogarNovamente == 1)
            {
                
                 printf ("\n \n  Escolhas: \n 1- Para Pedra \n 2- Para Papel \n 3- Para Tesoura \n ");
              
                 printf ("\n \n Vez do Jogador :");
                 scanf ("%d" , &jogada1);
                 
                    while (jogada1>3 || jogada1<1)
                {
                    printf("Opcao Invalida! Tente novamnete:");
                    scanf("%d" , &jogada1);
                }
                
                 srand(time(NULL));
                 printf ("\n \n Vez do Computador:" , rand() % 3);
                 jogada2 = (rand() % 3) +1;
                 printf("%d" , jogada2);
                 
                    if ( jogada1 == 1 && jogada2 == 2 )
                    {
                       printf("\n RESULTADO: Papel ganha da pedra, Ganhador: Computador");
                       partidas++;
                       vencimento2++;
                       
                    }else{
                        
                        if ( jogada1 == 2 && jogada2 == 1 )
                        {
                       printf("\n RESULTADO: Papel ganha da pedra, Ganhador: Jogador ");
                       partidas++; 
                       vencimento1++;           
                       
                        }else{
                            
                            if ( jogada1 == 1 && jogada2 == 3 )
                            {
                             printf("\n RESULTADO: Pedra ganha da tesoura, Ganhador: Jogador ");
                             partidas++;
                             vencimento1++;
                             
                            }else{
                                
                                if ( jogada1 == 3 && jogada2 == 1 )
                                
                                {
                                 printf("\n RESULTADO: Pedra ganha da tesoura, Ganhador: Computador");
                                 partidas++;
                                 vencimento2++;
                                 
                                }else{
                                    
                                    if ( jogada1 == 3 && jogada2 == 2)
                                    {
                                     printf (" \n RESULTADO: Tesoura ganha do papel, Gahador: Jogador ");
                                     partidas++;
                                     vencimento1++;
                                        
                                    }else{
                                        
                                        if ( jogada1 == 2 && jogada2 == 3 )
                                        {
                                         printf("\n RESULTADO: Tesoura ganha do papel, Ganhador: Computador");
                                         partidas++;
                                         vencimento2++;
                                            
                                        }else{
                                            
                                            printf ("\n Houve Empate!");
                                            empates++;
                                            
                                            
                                            }
                                        
                                        }
                                     }
                                }
                            }
                        }
                        
                printf("\n \n Para jogar novamente digite = 1 ou sair digite = 2 : ");
                scanf("%d" , &jogarNovamente );
                
                while (jogarNovamente<1 || jogarNovamente>2)
                {
                    printf("Opcao Invalida! Tente novamnete:");
                    scanf("%d" , &jogarNovamente);
                }
                
            } 
            
        totalPartidas=partidas+empates; 
        vitorias1=(100*vencimento1)/partidas;
        vitorias2=(100*vencimento2)/partidas;
    
        printf(" \n ==============\n |ESTATISTICAS| \n ==============\n Quantidade de Partidas: %d | Quantidade de Empates: %d" , totalPartidas , empates) ;
        printf("\n Percentual de Vitotias do Jogador: %f  \n Percentual de Votorias do Computador: %f " , vitorias1 , vitorias2);
                
        break;
        
    }
    

    return 0;
}

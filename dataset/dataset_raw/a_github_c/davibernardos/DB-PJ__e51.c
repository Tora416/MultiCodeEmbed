#include <stdio.h>
#include <stdlib.h>
#include <math.h>


int main(int argc, char *argv[]) 
{
    float valorIngresso, meiaEntrada, valorPago, troco;
    int opcao, capacidadeMaxima, tipoIngresso, x, y, quantidadeVendido, quantidadeRestante;
    char evento;    
    
    capacidadeMaxima = 0;
    quantidadeRestante = 1;
    x = 0;
    y = 0;
    
    printf("\t____________________________________________________________\n");
    printf("\n");
    printf("\t| Ingresso++ - Meu sistema de gestao de venda de ingressos |\n");
    printf("\n");
    printf("\t____________________________________________________________\n");
    printf("\n");
    
    while (y == 0)
    {
        while (x <= 50)
        {
            printf("_");
            x++;                
        }
            
        x = 0;
        
        
        printf("\n");           
        printf("\n1) Cadastro de Evento.\n");
        printf("2) Compre seu ingresso.\n");
        printf("3) Sair.\n");
        printf("\n");       
            
        printf("Digite a opcao desejada: ");
        scanf("%d", &opcao);
        printf("\n");
    
        switch (opcao)
        {
            case 1:
                printf("\t-Digite o nome do evento: ");
                scanf("%s", &evento);
                printf("\n\t-Informe a capacidade maxima de pessoas: ");
                scanf("%d", &capacidadeMaxima);
                printf("\n\t-Digite o valor de cada ingresso: ");
                scanf("%g", &valorIngresso);
                
                
                meiaEntrada = valorIngresso * 0.4;
                quantidadeVendido = 0;  
                quantidadeRestante = capacidadeMaxima;      
            break;
            case 2:
            
                if (capacidadeMaxima == 0)
                {
                    printf("Nao ha evento cadastrado\n");   
                }
                else
                {       
                    
                        
                    if(quantidadeRestante <= 0)
                    {
                    
                    printf("Ingresso Esgotados!\n");
                        
                    }
                    else
                    {                       
                        printf("\t_______________________________________\n");
                        printf("\n\t| ADQUIRA SEU INGRESSO PARA O EVENTO. |\n");
                        printf("\t_______________________________________\n");
                        
                        printf("\n\t\tO valor do evento eh: R$%.2f \n\t\t(Meia entrada: R$%.2f)\n", valorIngresso, meiaEntrada);
                        
                        printf("\nEscolha o tipo de ingresso:\n");
                        printf("\n\t-Digite 1 para inteira.\n");
                        printf("\t-Digite 2 para meia.\n\n\t\t");   
                        scanf("%d", &tipoIngresso); 
                        
                            
                        switch (tipoIngresso) 
                        {
                            case 1: 
                                printf("\n\nInsira o dinheiro: ");
                                scanf("%g", &valorPago);
                                    
                                if (valorPago < valorIngresso)
                                {
                                        printf("Valor pago insuficiente!\n");                       
                                }
                                else
                                {
                                    if (valorPago > valorIngresso)  
                                    {
                                        troco = valorPago - valorIngresso;                                  
                                        printf("\nSeu troco eh: R$%g\n", troco);                            
                                    }
                                        printf("\nCompra concluida!\n");
                                        
                                        quantidadeVendido++;                                    
                                }
                            break; 
                            case 2: 
                                printf("Insira o dinheiro: ");
                                scanf("%g", &valorPago);
                                
                                if (valorPago < meiaEntrada)
                                {
                                    printf("Valor pago insuficiente!\n");                       
                                }
                                else
                                {
                                    if (valorPago > meiaEntrada)
                                    {
                                        troco = valorPago - meiaEntrada;                                    
                                        printf("\nSeu troco eh: R$%g\n", troco);                            
                                    }
                                    printf("\nCompra concluida!\n");
                                            
                                    quantidadeVendido++;
                                }               
                            break;
                            default:
                                printf("Opcao invalida.\n");
                            break;
                                                                                                
                        } 
                    
                    quantidadeRestante = capacidadeMaxima - quantidadeVendido;
                printf("\n\tQuantidade de entrada inteira restantes: %d\n", quantidadeRestante);                
                printf("\tQuantidade de meia entrada restantes: %d\n", quantidadeRestante);
                    
                    }
                }
            break; 
                        
            case 3:
                y = 1;
            break;  
            
            default:
                printf("Opcao invalida.\n");
            break;  
                
                
        } 
    } 
    
    return 0;
}

#include <stdio.h>
#include <stdlib.h>

void main(){
    char nome [60];
    int capacidadeMax, operacao, disponivelMeia, confirmacao, vendidoMeia, vendidoInteira;
    float valorInteira, meiaEntrada, valorTotal, troco;
    vendidoMeia = 0;
    vendidoInteira = 0;
        
    printf("Ingressos++_Meu sistema de gestao de vendas de ingressos. \n");
    printf("\n\n Cadastre o seu evento. \n");
    printf("Nome do evento: \n");
    gets(nome);
    printf("Valor da entrada: \n");
    scanf("%f", &valorInteira);
    meiaEntrada = valorInteira/2;
    printf("Capacidade maxima do local: \n");
    scanf("%d", &capacidadeMax);
    disponivelMeia = capacidadeMax*0.4;
    
    printf("\n\n Evento: %s \n", nome);
    printf("Capacidade maxima de %d lugares \n", capacidadeMax);
    printf("Valor da entrada Inteira: %g \n",valorInteira);
    printf("Valor da Meia entrada: %g \n",meiaEntrada);
                
    while(operacao != 3){
    
    printf("\n\n Para comprar o seu ingresso escolha: \n");
    printf("[1] - Valor inteiro \n");
    printf("[2] - Meia entrada \n");
    printf("[3] - Finalizar vendas \n");
    scanf("%d", &operacao);
    switch(operacao){
        case 1:
            
            if(capacidadeMax > 0){
            
                         
                printf("Valor da compra: %g", valorInteira);
                printf("\n\n Concluir: \n");
                printf("[1] - SIM \n");
                printf("[2] - NAO \n");
                scanf("%d", &confirmacao);
                
                if(confirmacao == 1)
                    printf("\n Valor do ingresso: %g", valorInteira);
                    printf("\n Digite o valor pago: \n");
                    scanf("%g", &valorTotal);
                    if(valorTotal >= valorInteira){
                                    
                    troco = valorTotal - valorInteira;
                    printf("\n troco: %g \n", troco);
                
                }else{
                    printf("Valor insuficiente para concluir a compra.");
                    break;
                }   
                    printf("\n Compra efeituada com exito.");
                    capacidadeMax = capacidadeMax - 1;
                    vendidoInteira++;
                                        
                    break;
                    
                }else{
                    printf("Ingressos esgotados. \n");
                    break;
                }
            
                    
        case 2:
            if(disponivelMeia > 0){
                
                printf("\n Valor do ingresso: %g", meiaEntrada);
                printf("\n Confirmar: \n");
                printf("[1] - SIM \n");
                printf("[2] - NAO \n");
                scanf("%d", &confirmacao);
                
                if(confirmacao == 1){
                    printf("\n Valor do ingresso: %g",meiaEntrada);
                    printf("\n Digite o valor pago: \n");
                    scanf("\n %g", &valorTotal);
                                                        
                    if(valorTotal >= meiaEntrada){
                    
                    troco = valorTotal - meiaEntrada;
                    printf("\n troco: %g \n\n", troco);
                    
                    printf("Compra comcluida com exito. \n");
                    disponivelMeia = disponivelMeia - 1;
                    capacidadeMax = capacidadeMax - 1;
                    vendidoMeia++;
                    break;
                        
                    }else{
                        printf("\n quantia insuficiente");
                        break;
                    }   
                                                
                }else{
                printf("Ingressos de meia entrada esgotados. \n");
                break;
                }
            }
        
        case 3: 
                printf("\nTotal de ingressos tipo inteira vendido: %d \n", vendidoInteira);
                printf("Total de ingressos tipo meia vendido: %d \n", vendidoMeia);
                printf("Ingressos disponiveis: %d \n", capacidadeMax);
                            
                break;
                
        default: 
            
                printf("Opcao invalida.");  
            
                break;
            
    }
}

}









    
    


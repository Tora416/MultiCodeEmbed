#include <stdio.h>
#include <stdlib.h>

void main(){
    char nome[50];
    int capacidade,operacao,capacidadeMeiaEntrada,confirmacao,vendidoMeia,vendidoInteira;
    float valorInteira,meiaEntrada,valorPago,troco;
    vendidoMeia = 0;
    vendidoInteira = 0;
    
    printf("Ingressos++");
    printf("\nCadastre um evento");
    printf("\nNome do evento: \n");
    gets(nome);
    printf("\nCapacidade maxima: \n");
    scanf("%d", &capacidade);
    capacidadeMeiaEntrada = capacidade*0.4;
    printf("\nValor da entrada: \n");
    scanf("%g", &valorInteira);
    meiaEntrada = valorInteira/2;
    
    printf("\nEvento: %s", nome);
    printf("\nCapacidade maxima de %d", capacidade);
    printf("\nValor da entrada(Inteira): %g",valorInteira);
    printf("\nValor da entrada(Meia): %g",meiaEntrada);
    
    sleep(4);
    system("cls"); 
        
    while(operacao != 3){
    
    printf("\nComprar ingresso");
    printf("\n[1] - Valor inteiro");
    printf("\n[2] - Meia entrada");
    printf("\n[3] - Finalizar vendas\n");
    scanf("%d", &operacao);
    switch(operacao){
        case 1:
            
            printf("\nValor da compra: %g", valorInteira);
                printf("\n Confirmar:");
                printf("\n[1] - SIM");
                printf("\n[2] - NAO\n");
                scanf("%d", &confirmacao);
                
                if(confirmacao == 1){
                    printf("\nValor do ingresso: %g", valorInteira);
                    printf("\nValor pago\n");
                    scanf("%g", &valorPago);
                    if(valorPago >= valorInteira){
                    
                    troco = valorPago - valorInteira;
                    printf("\nTroco: %g", troco);
                    
                    printf("\nIngresso comprado com sucesso!");
                    capacidade = capacidade - 1;
                    vendidoInteira++;
                    
                    printf("\nValor do ingresso: %g \nvalor pago: %g \ntroco: %g",valorInteira,valorPago,troco);
                    break;
                }else{
                    printf("\nQuantia insuficiente!");
                    break;
                }
                }else{
                    printf("\nOperacao finalizada!");
                    break;
                }
            
            
        case 2:
            if(capacidadeMeiaEntrada > 0 ){
                
                printf("\nValor do ingresso: %g", meiaEntrada);
                printf("\nConfirmar:");
                printf("\n[1] - SIM");
                printf("\n[2] - NAO\n");
                scanf("%d", &confirmacao);
                if(confirmacao == 1){
                    printf("\nValor do ingresso: %g",meiaEntrada);
                    printf("\nValor pago:\n");
                    scanf("%g", &valorPago);
                    if(valorPago>=meiaEntrada){
                    
                    troco = valorPago - meiaEntrada;
                    printf("\nTroco: %g", troco);
                    
                    printf("\nIngresso comprado com sucesso!");
                    capacidadeMeiaEntrada = capacidadeMeiaEntrada - 1;
                    capacidade = capacidade - 1;
                    vendidoMeia++;
                    printf("\nValor do ingresso: %g \nValor pago: %g \nTroco: %g",meiaEntrada,valorPago,troco);
                    break;
                    }else{
                        printf("\nQuantia insuficiente!");
                        break;
                    }
                }else{
                    printf("\nOperacao finalizada!");
                    break;
                }
                
            }else{
                printf("\nIngressos de meia entrada esgotados!");
                break;
            }
        
        case 3: 
            printf("\nTotal de ingressos vendidos tipo inteira: %d", vendidoInteira);
            printf("\nTotal de ingressos vendidos tipo meia: %d", vendidoMeia);
            printf("\nIngressos disponiveis inteira: %d", capacidade);
            printf("\nIngressos disponiveis meia: %d", capacidadeMeiaEntrada);
            
            break;
                
        default: 
            printf("\nIngressos esgotados");    
            sleep(5);
            break;
    }
}
    
    
    
}

#include <stdio.h>
#include <stdlib.h>



int main(int argc, char *argv[]) 
{
    int capacidadeMaxima, ingressoComprado, opcao, escolha, contInteira, tipo, contMeia, ingressosRestantes;
    float entradaInteira, meiaEntrada, valorPagar, pagamento, totalPagar;
    char nomeEvento[30]; 

    printf("Digite o nome do Evento: ");
    scanf("%s", &nomeEvento);
    printf("\nDigite a capacidade maxima: ");
    scanf("%d", &capacidadeMaxima);
    printf("\nDigite o valor da entrada inteira: ");
    scanf("%g", &entradaInteira);   
        

    
    contInteira = 0;
    contMeia = 0;
    
    system("cls");
    
    
    
    while(opcao != 2)
    {
        system("cls");
        
        printf("Menu\n");
        printf("\n(1) Comprar Ingressos \n");
        printf("(2) Sair \n\n");
        printf("Digite a opcao desejada: ");
        scanf("%d", &opcao);
        
        if((contInteira + contMeia) == capacidadeMaxima)
        {
            opcao = 0;
            printf("Ingressos Esgotados !\n");
            system("pause");
        }
        
        
        system("cls");
        
        
        
        if(opcao == 1)
        {
            ingressoComprado= 0;
            printf("Nome do Evento: %s\n", nomeEvento);
            printf("Capacidade Maxima: %d\n", capacidadeMaxima);
            printf("O Valor da Entrada Inteira: %g\n\n", entradaInteira);
            
            printf("\nIngressos:\n");
            printf("\n(1) Entrada Inteira\n");
            printf("(2) Meia Entrada\n\n");
            printf("Escolha a opcao desejada: ");
            scanf("%d", &escolha);
            
            
            if(escolha == 1)
            {
                valorPagar = entradaInteira;
                printf("\nValor a pagar: %g", valorPagar);
                contInteira++;
            }
            else
            {
                valorPagar = entradaInteira / 2;
                printf("\nValor a pagar: %g", valorPagar);
                contMeia++;
            }
            
            
            while(ingressoComprado == 0)
            {
                printf("\n\nForma de Pagamento:\n");
                printf("\n(1) Somente em Dinheiro\n");
                printf("\nDigite 1 para iniciar o pagamento:");
                scanf("%d", &tipo);
                
                if(tipo == 1)
                {
                    printf("\nDigite o valor em dinheiro:");
                    scanf("%g", &pagamento);
                    totalPagar = pagamento - valorPagar;
                    
                    if(totalPagar < 0)
                    {
                        printf("\nValor menor que valor total do ingresso\n\n");
                    }
                    else 
                    {
                        printf("\ntroco eh: %g", totalPagar);
                        ingressoComprado = 1;
                    }
                    
                }
                else
                {
                    printf("Pagamento somente em dinherio !\n\n");
                }
            }
            
        
            
            printf("\n\nIngressos Comprado\n\n");
            system("pause");
                                
        }
        else if(opcao == 2)
        {
            printf("Total de ingressos: %d\n", capacidadeMaxima);
            ingressosRestantes = capacidadeMaxima - ingressoComprado;
            printf("\nSobraram: %d\n\n", ingressosRestantes);
            system("pause");
        }
    }
    
    
    
    
    return 0;
}

#include <stdio.h>
#include <stdlib.h>



struct data
{
    int dia;
    int mes;
    int ano;    
};



int main(int argc, char *argv[]) 
{
    int capacidadeMaxima, ingressoComprado, opcao, escolha, contInteira, tipo, contMeia, ingressosRestantes, formaPagamento;
    float entradaInteira, meiaEntrada, valorPagar, pagamento, totalPagar;
    char nomeEvento[30]; 
    struct data diaEvento;
    
    

    opcao = 2;
    
while(opcao == 2)
{
    printf("Criar evento:\n");
    printf("\nDigite o nome do Evento: ");
    scanf("%s", &nomeEvento);
    printf("\nDigite o data que o evento ira acontecer: ");
    scanf("%d/%d/%d", &diaEvento.dia, &diaEvento.mes, &diaEvento.ano);
    printf("\nDigite a capacidade maxima: ");
    scanf("%d", &capacidadeMaxima);
    printf("\nDigite o valor da entrada inteira: ");
    scanf("%g", &entradaInteira);   
        

    
    contInteira = 0;
    contMeia = 0;
    ingressoComprado = 0;
    
    system("cls");
    opcao = 0;
    
    
    
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
            
            while(escolha !=1 && escolha !=2)
            {
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
                else if(escolha == 2)
                {
                    valorPagar = entradaInteira / 2;
                    printf("\nValor a pagar: %g", valorPagar);
                    contMeia++;
                }else
                {
                    printf("\nOpcao Invalida!");
                    
                }
            
            }
            escolha = 0;
            while(ingressoComprado == 0)
            {
                printf("\n\nEscolha a Forma de Pagamento:\n");
                printf("\nDigite 1 para pagar em dinheiro ou 2 para pagar com cartao:");
                scanf("%d", &tipo);
                
                while(tipo == 1 || tipo == 2)
                {
                
                    if(tipo == 1)
                    {
                        printf("\nDigite o valor em dinheiro:");
                        scanf("%g", &pagamento);
                        totalPagar = pagamento - valorPagar * 0.9;
                        
                        
                        
                        if(totalPagar < 0)
                        {
                            printf("\nValor menor que valor total do ingresso\n\n");
                            system("pause");
                        }
                        else 
                        {
                            printf("\ntroco eh: %g", totalPagar);
                            ingressoComprado++;
                            break;
                        }               
                    }
                    else
                    {
                        if(tipo == 2)
                        {
                            while(formaPagamento !=1 && formaPagamento !=2)
                            {
                            
                                printf("\nPagamento sendo realizado no cartao!\n");
                                printf("\nDigite 1 para Debito!\n");
                                printf("\nDigito 2 para credito!\n");
                                printf("\nEscolha opcao desejada:");
                                scanf("%d", &formaPagamento);
                                
                                if(formaPagamento == 1)
                                {
                                    printf("\nPagamento realizado no debito!\n");
                                    ingressoComprado++;
                                    
                                    
                                }
                                else if(formaPagamento == 2)
                                {       
                                    printf("\nPagamento realizado no credito!\n");
                                    ingressoComprado++;
                                
                                    
                                }else
                                {
                                    printf("\nOpcao Invalida!\n");
                                }
                            }
                            formaPagamento= 0;
                            
                        }
                        
                        break;
                    }
                    
                
                    
                }
            
            }
            
        
            printf("\n\nIngresso Comprado\n\n");
            system("pause");    
            
                                
        }
        else if(opcao == 2)
        {
            printf("Total de ingressos: %d\n", capacidadeMaxima);
            ingressosRestantes = capacidadeMaxima - ingressoComprado;
            printf("\nSobraram: %d\n\n", ingressosRestantes);
            printf("Ingressos comprados Entrada Inteira: %d\n", contInteira);
            printf("\nIngressos comprados Meia Entrada: %d\n\n", contMeia);
            system("pause");
        }
        
        system("cls");
    }
    
    
    
}
    return 0;
}

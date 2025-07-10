#include <stdio.h>
#include <stdlib.h>
#include <math.h>

float valorIngresso, meiaEntrada;
int capacidadeMax, capacidadeMeia, capacidadeInteira, iComprados, mComprados, contEvento, evento;
char nomeEvento[31][30];
int capacidade[31];
float preco[31];
int capacidadeI[31], capacidadeM[31];

void cabecalho()
{
    printf("\t____________________________________________________________\n");
    printf("\n");
    printf("\t| Ingresso++ - Meu sistema de gestao de venda de ingressos |\n");
    printf("\n");
    printf("\t____________________________________________________________\n");
    printf("\n");
}


void cadastrarEvento()
{
    
    fflush(stdin);
    printf("\t-Digite o nome do evento: ");
    gets(nomeEvento[contEvento]);
    
    fflush(stdin);

    printf("\n\t-Informe a capacidade maxima de pessoas: ");
    scanf("%d", &capacidadeMax);
    capacidade[contEvento] = capacidadeMax;
        
    capacidadeMeia = 0.4*capacidadeMax;
    capacidadeInteira = 0.6*capacidadeMax;
    
    capacidadeI[contEvento] = capacidadeInteira;
    capacidadeM[contEvento] = capacidadeMeia;
            
    printf("\n\t-Digite o valor de cada ingresso: ");
    scanf("%g", &valorIngresso);
    preco[contEvento] = valorIngresso;
                
            
        contEvento++;   
}

int selecionarEvento()
{
    int contadorLista, existeEvento;
    
    printf("\t\t\t\t\t\tEventos Cadastrados: \n");
    printf("\n\t\t\tNOME\t\t \t\tCAPACIDADE\t\t \t\tPRECO\n\n");
    for(contadorLista = 0; contadorLista < 31; contadorLista++)
    {
        if(capacidade[contadorLista] != 0)
        {
            printf("%d)\t%s\t\t\t\t\t\t%d pessoa(s)\t\t\t\tR$%.2f\n", contadorLista, nomeEvento[contadorLista], capacidade[contadorLista], preco[contadorLista]);
        }
    }
    
        printf("\n\n Digite o numero do evento desejado: ");
        scanf("%d", &evento);
        
        if(capacidade[evento] != 0)
        {
            capacidadeMax = capacidade[evento];
            valorIngresso = preco[evento];
            capacidadeInteira = capacidadeI[evento];
            capacidadeMeia = capacidadeM[evento];
            
            
            
            existeEvento = 1;
        }
            else
            {
                existeEvento = 0;
            }
    
    return existeEvento;
    
}


int escolherIngresso()
{   
    int tipoIngresso;
    

    meiaEntrada = valorIngresso*0.5;
    
        printf("\t_______________________________________\n");
        printf("\n\t| ADQUIRA SEU INGRESSO PARA O EVENTO. |\n");
        printf("\t_______________________________________\n");
            
        printf("\n\t\tO valor do evento eh: R$%.2f \n\t\t(Meia entrada: R$%.2f)\n", valorIngresso, meiaEntrada);    
                        
        printf("\nEscolha o tipo de ingresso:\n");
        printf("\n\t-Digite 1 para inteira.\n");
        printf("\t-Digite 2 para meia.\n\n\t\t");   
        scanf("%d", &tipoIngresso); 
        
        return tipoIngresso;
}

void comprarIngresso(int ingresso, float desconto)
{
    
    float valorPago, troco;
    
    
        
        switch (ingresso) 
        {
        case 1: 
            if(capacidadeInteira > 0)
            {           
        
                printf("\n\nInsira o dinheiro: ");
                scanf("%g", &valorPago);
                                        
                if (valorPago < (valorIngresso - (valorIngresso*desconto)))
                {
                    printf("Valor pago insuficiente!\n");                       
                }
                    else
                    {
                        if (valorPago > (valorIngresso -(valorIngresso*desconto)))
                        {
                            troco = valorPago - (valorIngresso - (valorIngresso*desconto));                                 
                            printf("\nSeu troco eh: R$%g\n", troco);                            
                        }
                    printf("\nCompra concluida!\n");                
                    
                    capacidadeInteira--;
                    capacidadeI[evento] = capacidadeInteira;
                                        
                    printf("\nevento: %d", capacidadeI[evento]);
                    printf("\n\tInteiros restantes: %d\n", capacidadeInteira);
                    
                    iComprados = (capacidadeMax*0.6)-capacidadeInteira;
                    printf("\n\tInteiros comprados: %d\n", iComprados);
                        
                
                    }
            }
            else
                {
                    printf("\t\t\nEntradas inteiras esgotadas!\n");
                }
        break;
        case 2: 
            if(capacidadeMeia > 0)
            {
                            
                printf("Insira o dinheiro: ");
                scanf("%g", &valorPago);
                    
                if (valorPago < (meiaEntrada - (meiaEntrada*desconto)))
                {
                    printf("Valor pago insuficiente!\n");                       
                }
                    else
                    {
                        if (valorPago > (meiaEntrada - (meiaEntrada*desconto)))
                        {
                            troco = valorPago - (meiaEntrada - (meiaEntrada*desconto));                                 
                            printf("\nSeu troco eh: R$%g\n", troco);                            
                        }
                        printf("\nCompra concluida!\n");
                                            
                    capacidadeMeia--;
                    capacidadeM[evento] = capacidadeMeia;
                                    
                    printf("\n\tMeia entrada restantes: %d\n", capacidadeMeia);
                    
                    mComprados = (capacidadeMax*0.4)-capacidadeMeia;
                    printf("\n\tMeia entrada compradas: %d\n", mComprados);
                    
                    capacidadeM[evento] = capacidadeMeia;
                    }   
            }
                else
                {
                    printf("\t\t\nMeias entradas esgotadas!\n");
                }
                            
        break; 
        default:
            printf("Opcao invalida.\n");
        break;
        }
}

void menuIngresso()
{                       
    int pagamento, existeEvento;
        
    if (capacidadeMax == 0)
    {
        printf("Nao ha evento cadastrado\n");   
    }
        else
        {   
            existeEvento = selecionarEvento();
            
            if(existeEvento == 1)   
            {
                printf("\n\t\t\t\t(10%% de desconto no dinheiro)\n\n");
                printf("\n Digite 1 para pagamento no cartao: ");           
                printf("\n Digite 2 para pagamento em dinheiro: \n\t");
                scanf("%d", &pagamento);
            
            
                if(pagamento == 1)
                {           
                comprarIngresso(escolherIngresso(), 0);
                }
                    else
                    {
                        comprarIngresso(escolherIngresso(), 0.1);
                    }
            }
                else
                {
                    printf("\n\n\tNao existe esse evento!\n");
                }   
        }
}





int main(int argc, char *argv[]) 
{
    int opcao, loop;
    
    contEvento = 0;
    loop = 0;   
    
    cabecalho();
    
    while(loop == 0)
    {
    
    
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
                cadastrarEvento();
            break;
            case 2: 
                menuIngresso();
            break;
            case 3:
                loop = 1;
            break;
            default:
                printf("Opcao invalida!\n");
            break;
            
        }   
    }
    
    
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

    
int contShow;

struct evento{
    char nome[20];
    float valorIngresso;
    int cadeiras;
    int disponiveis;
    float lucro;
    int meia;
};

struct evento show[10];

    
void cadastrarEvento(struct evento show[])
{   
    printf("Informe o nome do evento:\n");
    fflush(stdin);
    gets(show[contShow].nome);
    printf("Informe o valor do ingresso: \n");
    scanf("%g", &show[contShow].valorIngresso);
    printf("Informe a quantidade de lugares disponiveis: \n");
    scanf("%d", &show[contShow].cadeiras);
    show[contShow].disponiveis = show[contShow].cadeiras;
    show[contShow].lucro = 0;
    show[contShow].meia = 0;
}

void listarEventos(struct evento show[])
{
    int cont;
    
    for(cont = 0; cont < contShow; cont++)
    {   
        printf("Evento: %s\n", show[cont].nome);
        printf("Valor da entrada: %g\n", show[cont].valorIngresso);
        printf("Lugares disponiveis: %d\n", show[cont].disponiveis);
        printf("Codigo: %d \n\n\n", cont);
    }
}

float pagarDinheiroInt(int contSelec , float pagamento, struct evento show[])
{
    float troco;
    
    show[contSelec].lucro += (show[contSelec].valorIngresso * 0.9);
    troco = pagamento - (show[contSelec].valorIngresso * 0.9);
    show[contSelec].disponiveis--;
    
    return troco;
}

float pagarDinheiroMeia(int contSelec, float pagamento, struct evento show[])
{
    float troco;
    
    show[contSelec].lucro += (show[contSelec].valorIngresso * 0.9) / 2;
    troco = pagamento - (show[contSelec].valorIngresso * 0.9) / 2;
    show[contSelec].disponiveis--;
    show[contSelec].meia++;
    
    return troco;
}

void pagarCartaoInt(int contSelec, struct evento show[])
{
    show[contSelec].lucro += show[contSelec].valorIngresso;
    show[contSelec].disponiveis--;
}

void pagarCartaoMeia(int contSelec, struct evento show[])
{
    show[contSelec].lucro += show[contSelec].valorIngresso / 2;
    show[contSelec].disponiveis--;
    show[contSelec].meia++;
}

void informarDados(struct evento show[])
{
    int cont, vendidos;
    
    for(cont = 0; cont < contShow; cont++)
    {
        printf("Evento: %s \n", show[cont].nome);
        printf("Total arrecadado: %g \n", show[cont].lucro);
        vendidos = show[cont].cadeiras - show[cont].disponiveis;
        printf("Ingressos totais vendidos: %d \n", vendidos);
        printf("Ingressos de meia entrada vendidos: %d \n", show[cont].meia);
        printf("Ingressos restantes: %d \n\n\n", show[cont].disponiveis);
    }
}


    
int main(int argc, char *argv[]) {

    float pagamento, troco, restante;
    int menu, contOpera, contSelec;
    
    
    contSelec = 0;
    contShow = 0;
    contOpera = 0;

    while(contOpera <= 0)
    {

        printf("Iniciando cadastro de eventos \n\n");   
        printf("Informe a opcao desejada:\n");
        printf("Digite 1 para cadastrar um evento \n");
        printf("Digite 2 iniciar vendas \n");
    
        scanf("%d", &menu);
        
        switch(menu)
        {
            case 1:
            {
                cadastrarEvento(show);
                contShow++;
                system("cls");
                break;
            }
            case 2:
            {
                printf("Iniciando operacao de vendas\n");
                contOpera++;
                break;
            }
            default:
            {
                printf("Informe uma opcao valida\n");
                break;
            }       
        }   
        if(contShow >= 10)
        {
            printf("Limite de eventos atingido, prosseguindo para venda de ingressos.\n");
            contOpera++;
        }
    }


    while(contOpera <= 1)
    {
        do{
        printf("Escolha o codigo do evento que deseja participar: \n");
        listarEventos(show);
        scanf("%d", &contSelec);
        if(show[contSelec].disponiveis <= 0)
        {
            printf("Ingressos para este evento estao esgotados, retornando para a selecao. \n");
        }
        }while(show[contSelec].disponiveis <= 0);
        
        printf("Informe a opcao desejada:\n");
        printf("Digite 1 para comprar um ingresso inteiro. \n");
        printf("Digite 2 para comprar meia entrada. \n");
        printf("Digite 3 para mudar o evento selecionado. \n");
        printf("Digite 4 para fechar as operacoes. \n");
    
        scanf("%d", &menu);
        
        switch(menu)
        {
            case 1:
            {
                printf("Escolha a forma de pagamento: \n");
                printf("Pressione 1 para pagamento em dinheiro com desconto ou 2 para pagamento em cartao.\n");
                scanf("%d", &menu);
                switch(menu)
                {
                    case 1:
                    {
                        printf("Valor a ser pago: %g\n", (show[contSelec].valorIngresso * 0.9));            
                        printf("Informe o valor do pagamento: ");
                        do
                        {
                            scanf("%g", &pagamento);
                            if(pagamento < (show[contSelec].valorIngresso * 0.9))
                            {
                                restante = (show[contSelec].valorIngresso * 0.9) - pagamento;
                                printf("Valor inserido insufuciente, faltou %g, insira o valor correto para prosseguir.\n", restante);  
                            }
                        }while(pagamento < (show[contSelec].valorIngresso * 0.9));
                        troco = pagarDinheiroInt(contSelec, pagamento, show);
                        printf("Seu troco e de: %g\n", troco);                      
                        break;
                    }
                    case 2:
                    {
                        pagarCartaoInt;
                        break;
                    }
                }
                system("cls");
                break;
            }
            
            case 2:
            {
                if(show[contSelec].meia <= show[contSelec].cadeiras * 0.4)
                {
                
                    printf("Escolha a forma de pagamento: \n");
                    printf("Pressione 1 para pagamento em dinheiro com desconto ou 2 para pagamento em cartao.\n");
                    scanf("%d", &menu);
                    switch(menu)
                    {
                        case 1:
                        {   
                            printf("Valor a ser pago: %g\n", (show[contSelec].valorIngresso * 0.9 / 2) );           
                            printf("Informe o valor do pagamento: ");
                            do
                            {
                                scanf("%g", &pagamento);
                                if(pagamento < ((show[contSelec].valorIngresso * 0.9 / 2)))
                                {
                                    restante = ((show[contSelec].valorIngresso * 0.9 / 2) ) - pagamento;
                                    printf("Valor inserido insufuciente, faltou %g, insira o valor correto para prosseguir.\n", restante);  
                                }
                            }while(pagamento < ((show[contSelec].valorIngresso * 0.9 / 2) ));
                            troco = pagarDinheiroMeia(contSelec, pagamento, show);
                            printf("Seu troco e de: %g \n", troco); 
                            break;
                        }
                        case 2:
                        {
                            pagarCartaoMeia;
                            printf("O pagamento foi efetuado com sucesso.\n");
                            break;
                        }
                    }
                }
                else
                {
                    printf("Ingressos para este evento estao esgotados. \n");
                }
                system("cls");
                break;              
            }
            
            case 3:
            {
                printf("Retornando para a selecao. \n");    
                system("cls");          
                break;
            }
            case 4:
            {
                printf("Encerrando operacao de vendas. \n");
                contOpera++;
                break;
            }
            default:
            {
                printf("Informe uma opcao valida. \n");
                break;
            }
        }
    }
    
    printf("Operacao de vendas encerradas.\n");
    informarDados(show);
    
    return 0;
}

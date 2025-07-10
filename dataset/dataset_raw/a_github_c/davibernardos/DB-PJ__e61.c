#include <stdio.h>
#include <stdlib.h>
#include <conio.h>




int main(int argc, char *argv[]) {
    
    
    char nomeEvento[20], localEvento[40], dataEvento[8], horaEvento[5];
    int detalhes, cadastro, qntdIngressos;
    int qntdInteiro, qntdMeio, tipoCompra;
    int capacMax;
    int contadorCompra;
    float vlrIngresso, vlrMeioIngresso;
    float vlrPago, vlrTroco, vlrSobra;
    
    
    do
    {
        system("cls");
        printf("-----------------------------------------------------------\n");
        printf("----------------   Vendedor de Ingressos   ----------------\n");
        printf("--------------    Configuracoes do Evento    --------------\n");
        printf("-----------------------------------------------------------\n\n\n");
        printf("Digite o nome do evento: ");
        setbuf(stdin, NULL);
        gets(nomeEvento);
        printf("\n      |Deseja adicionar detalhes ao evento?\n");
        do
        {
            printf("        |   1. Sim\n");
            printf("        |   2. Nao, desejo inserir as inforamcoes sobre os ingressos\n      |\n");
            printf("        |   Digite a opcao desejada: ");
            scanf("%d", &detalhes);
                switch(detalhes)
                {
                    case 1:
                        printf("        |\n     |Digite a data do evento (dd/mm/aa): ");
                        setbuf(stdin, NULL);
                        gets(dataEvento);
                        printf("        |\n     |Digite a hora do evento (hh:mm): ");
                        setbuf(stdin, NULL);
                        gets(horaEvento);
                        printf("        |\n     |Digite o local do evento (cidade, bairro, rua e logradouro): ");
                        setbuf(stdin, NULL);
                        gets(localEvento);
                        break;
                    case 2:
                        break;
                    default:
                        printf("\n      |opcao invalida, digite novamente.\n");
                }
        }
        while (detalhes>2 || detalhes<1);
        printf("\nDigite o total de ingressos a serem vendidos: ");
        scanf("%d", &qntdIngressos);
        printf("Digite o valor unitario de cada ingresso: R$");
        scanf("%f", &vlrIngresso);
        do
        {
            printf("\n\n\n          |Finalizar cadastro?                         |\n");
            printf("            |   1. Sim                               |\n");
            printf("            |   2. Nao, reenserir informacoes        |\n            |                                        |\n");
            printf("            |Digite a opcao desejada: ");
            scanf("%d", &cadastro); 
            if(cadastro >2 || cadastro<1)
            {
                printf("            |\n         |   Opcao invalida, digite novamente: ");
            }
        }
        while(cadastro>2 || cadastro<1);
    }
    while(cadastro==2);
    

    qntdMeio = qntdIngressos*0.4;
    qntdInteiro = qntdIngressos-qntdMeio;
    vlrMeioIngresso = vlrIngresso*0.5;
    capacMax = qntdIngressos;
        
    do
    {   
        system("cls");
        printf("---------------------------------------------------------\n");
        printf("| Auto atendimento - Venda de ingressos - %s | \n", nomeEvento);
        printf("---------------------------------------------------------\n");
        if(detalhes==1)
        {
            printf("\n  - Data: %s\n    - Hora: %s\n    - Local: %s", dataEvento, horaEvento, localEvento);
        }
        printf("\n  - Capacidade maxima: %d ", capacMax);
        printf("\n  - Valor unitario ingresso: R$ %.2f\n\n ", vlrIngresso);printf("__________________________________________________________");
        printf("\n\nDigite o tipo de ingresso que deseja comprar: ");
        printf("\n  1. Ingresso inteiro");
        printf("\n  2. Meio ingresso");
        printf("\n\n    Digite a opcao desejada: ");
        scanf("%d", &tipoCompra);
            switch(tipoCompra)
            {           
                case 1:
                    if(qntdInteiro > 0)
                    {
                        printf("\n\nValor a ser pago: R$%.2f", vlrIngresso);
                        do
                        {
                            printf("\n\nDigite o valor total que voce esta pagando a maquina: R$");
                            scanf("%g", &vlrPago);
                            if(vlrPago>vlrIngresso)
                            {
                                vlrTroco = vlrPago - vlrIngresso;
                                printf("Seu troco e: R$%.2f", vlrTroco);
                            }else{
                                if(vlrPago==vlrIngresso)
                                {
                                    printf("Nao ha troco.");;
                                }else{
                                    vlrSobra = vlrIngresso - vlrPago;
                                    printf("Precisa-se de mais R$%.2f para completar a compra do ingresso.", vlrSobra);
                                    }
                                }
                        }while(vlrPago<vlrIngresso);
                        qntdInteiro--;
                    }else{
                    printf("Infelizmente nao temos mais ingressos nesta categoria.");
                        }
                    break;
                case 2:
                    if(qntdMeio > 0)
                    {
                        printf("\n\nValor a ser pago: R$%.2f", vlrMeioIngresso);
                        do
                        {
                            printf("\n\nDigite o valor total que voce esta pagando a maquina: R$");
                            scanf("%g", &vlrPago);
                            if(vlrPago>vlrMeioIngresso)
                            {
                                vlrTroco = vlrPago - vlrMeioIngresso;
                                printf("Seu troco e: R$%.2f", vlrTroco);
                            }else{
                                if(vlrPago==vlrMeioIngresso)
                                {
                                    printf("Nao ha troco.");
                                }else{
                                    vlrSobra = vlrMeioIngresso - vlrPago;
                                    printf("Precisa-se de mais R$%.2f para completar a compra do ingresso.", vlrSobra);
                                    }
                                }
                        }while(vlrPago<vlrMeioIngresso);
                        qntdMeio--;
                    }else{
                    printf("\n- Infelizmente nao temos mais ingressos nesta categoria.");
                        }
                    break;
                default:
                    printf("\nOpcao invalida, digite novamente: ");
            }
        qntdIngressos = qntdInteiro + qntdMeio;
        printf("\n\n\nObrigado por comprar conosco!\n\n___________________________________________________________");
        printf("\n                        Relatorio                            ");
        printf("\n\n    Total de ingressos disponiveis = %d\n   Ingressos inteiros = %d Meio ingressos = %d", qntdIngressos, qntdInteiro, qntdMeio);
        printf("\n__________________________________________________________");
        if(qntdIngressos > 0)
        {
            do
            {
                printf("\n\n\nDeseja realizar uma nova compra?");
                printf("\n  1. Sim\n    2. Nao, desejo finalizar.");
                printf("\n\n    Digite a opcao desejada: ");
                scanf("%d", &contadorCompra);
            }while(contadorCompra < 1 && contadorCompra > 2);
        }
    }while(contadorCompra == 1 && qntdIngressos > 0);
    if(qntdIngressos == 0)
    {
        printf("\n\n\nNao ha mais ingressos disponiveis neste evento, todos foram vendidos.");
    }
    
return 0;
}

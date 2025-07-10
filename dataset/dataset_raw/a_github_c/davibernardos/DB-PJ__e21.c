#include <stdio.h>
#include <stdlib.h>



int main(int argc, char *argv[]) {
    char nomeEvento[50];
    int capacidadeMax;
    float valorEntradaInteira;
    float valorEntradaMeia;
    int ingressosInteiros;
    int ingressosMeios;
    int iInteirosVendidos;
    int iMeiosVendidos;
    int verificaCompra;
    int tipoIngresso;
    float valorPagamento;
    float valorPagamentoFaltante;
    float valorPagamentoFaltPago;
    int ingressosInteirosSobrantes;
    int ingressosMeiosSobrantes;
    float troco;
    float arrecadadoMeios;
    float arrecadadoInteiros;
    int tolalIngressosVendidos;
    float totalArrecadado;


    printf("Insira o Nome do evento \n");
    scanf("%s",&nomeEvento);
    printf("Insira a capacidade maxima \n");
    scanf("%d",&capacidadeMax);
    printf("Insira o valor da entrada inteira \n");
    scanf("%f",&valorEntradaInteira);
    valorEntradaMeia = valorEntradaInteira / 2;
    
    ingressosMeios =  capacidadeMax*0.4;
    ingressosInteiros = capacidadeMax - ingressosMeios;
    verificaCompra = 1;
    
    while(verificaCompra == 1){
        if(ingressosMeios == 0 && ingressosInteiros == 0){
            printf("Acabou os ingressos, fim do evento\n");
            verificaCompra++;
        }else{
            printf("-----------------------------------------------------------------------------\n");
            printf("Bem Vindo a compra de ingressos para o %s \n\n", nomeEvento);
            printf("Digite 1 para ingressos inteiros(%i) e 2 para meias(",ingressosInteiros);printf("%i) e 3 para cancelar\n", ingressosMeios);
            printf("-----------------------------------------------------------------------------\n");
            scanf("%d",&tipoIngresso);
            if(tipoIngresso == 1){
                if(ingressosInteiros == 0){
                    printf("Os ingressos inteiros estao esgotados\n");
                }else{
                    printf("Voce escolheu o ingresso inteiro que custa %.2f, favor indicar o valor que voce pagara\n", valorEntradaInteira);
                    scanf("%f",&valorPagamento);
                    while(valorPagamento < valorEntradaInteira){
                    valorPagamentoFaltante = valorEntradaInteira - valorPagamento;
                    printf("Favor pagar o total do ingresso, faltam R$%.2f\n", valorPagamentoFaltante);
                    scanf("%f",&valorPagamentoFaltPago);
                    valorPagamento = valorPagamentoFaltPago + valorPagamento;
                    }
                    if(valorPagamento > valorEntradaInteira){
                        troco = valorPagamento - valorEntradaInteira;
                        printf("O troco e de %.2f\n", troco);
                    }
                    ingressosInteiros = ingressosInteiros - 1;
                }
            }else{
                if(tipoIngresso == 2){
                    if(ingressosMeios == 0){
                        printf("Os ingressos meios estao esgotados\n");
                    }else{
                        printf("Voce escolheu o ingresso meio que custa %.2f, favor indicar o valor que voce pagara\n", valorEntradaMeia);
                        scanf("%f",&valorPagamento);
                        while(valorPagamento < valorEntradaMeia){
                        valorPagamentoFaltante = valorEntradaMeia - valorPagamento;
                        printf("Favor pagar o total do ingresso, faltam R$%.2f\n", valorPagamentoFaltante);
                        scanf("%f",&valorPagamentoFaltPago);
                        valorPagamento = valorPagamentoFaltPago + valorPagamento;
                        }
                        if(valorPagamento > valorEntradaMeia){
                            troco = valorPagamento - valorEntradaMeia;
                            printf("O troco e de %.2f\n", troco);
                        }
                        ingressosMeios = ingressosMeios - 1;
                    }
                }else{
                    if(tipoIngresso == 3){
                        break;
                    }else{
                    printf("Digite uma opcao valida \n");
                    }
                }
            }
            printf("Digite 1 para comprar mais um ingresso e 2 para finalizar as compras\n");
            scanf("%i", &verificaCompra);
            if(verificaCompra != 1 && verificaCompra != 2){
                printf("Digite uma opcao valida \n");
                verificaCompra = 1;
            }
        }
    }
    ingressosMeiosSobrantes =  capacidadeMax*0.4;
    ingressosInteirosSobrantes = capacidadeMax - ingressosMeiosSobrantes;
    ingressosMeiosSobrantes = ingressosMeiosSobrantes - ingressosMeios;
    ingressosInteirosSobrantes = ingressosInteirosSobrantes - ingressosInteiros;
    arrecadadoMeios = ingressosMeiosSobrantes * valorEntradaMeia;
    arrecadadoInteiros = ingressosInteirosSobrantes * valorEntradaInteira;
    tolalIngressosVendidos = ingressosInteirosSobrantes + ingressosMeiosSobrantes;
    totalArrecadado = arrecadadoMeios + arrecadadoInteiros;
    
    printf("-------------------------------------------------\n");
    printf("\nEvento %s ", nomeEvento);
    printf("finalizado.\n\nO total de ingressos inteiros vendidos foi de: %i;\nSobraram %i;\nTotal arrecadado R$%.2f.\n\nO total de ingressos meios vendidos foi de %i;\nSobraram %i;\nTotal arrecadado R$%.2f.\n\n", ingressosInteirosSobrantes,ingressosInteiros,arrecadadoInteiros,ingressosMeiosSobrantes,ingressosMeios,arrecadadoMeios);
    printf("O total de ingressos vendidos foi de %i.\nO total de dinheiro arrecadado foi de R$%.2f",tolalIngressosVendidos,totalArrecadado);
    return 0;
}



#include <stdio.h>
#include <stdlib.h>

int main() 
{
    float matriz[5][4], somaMes[100], somaSemana = 0, totalVendas = 0;
    int i, j;
    
    for(i = 0; i < 5; i++)
        for (j = 0; j < 4; j++)
        {
            printf("Digite as vendas da %d loja e %d semana:  ", i + 1, j+1);
            scanf_s("%f", &matriz[i][j]);
        }
    for (i = 0; i < 5; i++) 
    {
        somaMes[i] = 0;
        for (j = 0; j < 4; j++)
        {
            somaMes[i] += matriz[i][j];
        }
        somaSemana += somaMes[i];
        totalVendas += somaSemana;
    }
    for (i = 0; i < 5; i++)
        for (j = 0; j < 1; j++)
            printf("O total de vendas do mes do %d vendedor e %.2f:  \n", i+1, somaMes[i]);
            
    printf("O total de vendas de cada semana de todos os vendedores e %.2f:  \n", somaSemana);
    printf("O total de vendas do mes e %.2f:  \n", totalVendas);

    system("pause");
}

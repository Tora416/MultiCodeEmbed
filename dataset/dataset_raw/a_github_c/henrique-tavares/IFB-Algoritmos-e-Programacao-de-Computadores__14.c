#include <stdio.h>

int main()
{
    int hora_inicio, minuto_inicio, hora_fim, minuto_fim, minuto_total_inicio, minuto_total_fim, res_minuto, duracao_hora, duracao_minuto;

    scanf("%i", &hora_inicio);
    scanf("%i", &minuto_inicio);
    scanf("%i", &hora_fim);
    scanf("%i", &minuto_fim);

    minuto_total_inicio = (hora_inicio * 60) + minuto_inicio;
    minuto_total_fim = (hora_fim * 60) + minuto_fim;

    res_minuto = minuto_total_fim - minuto_total_inicio;

    duracao_hora = res_minuto / 60;
    duracao_minuto = res_minuto % 60;

    printf("\n\n");
    if (duracao_hora < 10)
    {
        printf("0%d", duracao_hora);
    }
    else
    {
        printf("%d", duracao_hora);
    }
    if (duracao_minuto < 10)
    {
        printf(":0%d", duracao_minuto);
    }
    else
    {
        printf(":%d", duracao_minuto);
    }
    printf("\n\n");
    return 0;
}
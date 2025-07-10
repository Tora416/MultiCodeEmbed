#include <stdio.h>

int main(void)
{
    float temp, frio, normal, quente;

    printf("\nInforme a temperatura ambiente em graus celsius: ");
    scanf("%f", &temp);

    
    
    
    if (temp < 20)
    {
        frio = 1;
        normal = 0;
        quente = 0;
    }

    
    
    
    else if ((temp >= 20) && (temp <= 26))
    {
        frio = 0;
        normal = 1;
        quente = 0;
    }

    
    
    
    else
    {
        frio = 0;
        normal = 0;
        quente = 1;
    }

    if (frio == 1)
    {
        printf("\nO aparelho está aquecendo\n\n");
    }
    else if (normal == 1)
    {
        printf("\nO aparelho está desligado\n\n");
    }
    else if (quente == 1)
    {
        printf("\nO aparelho está resfriando\n\n");
    }
}
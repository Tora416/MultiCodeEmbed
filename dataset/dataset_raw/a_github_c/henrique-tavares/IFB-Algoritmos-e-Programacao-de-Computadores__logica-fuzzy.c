#include <stdio.h>

int main(void)
{
    float temp;
    float frio, quente, normal;

    printf("\nInforme a temperatura do ambiente em graus celsius: ");
    scanf("%f", &temp);

    if (temp <= 10)
    {
        frio = 1;
        normal = 0;
        quente = 0;
        
    }
    else if ((10 < temp) && (temp <= 11))
    {
        frio = 0.9;
        normal = 0.1;
        quente = 0;
        
    }
    else if ((11 < temp) && (temp <= 12))
    {
        frio = 0.8;
        normal = 0.2;
        quente = 0;
        
    }
    else if ((12 < temp) && (temp <= 13))
    {
        frio = 0.7;
        normal = 0.3;
        quente = 0;
        
    }
    else if ((13 < temp) && (temp <= 14))
    {
        frio = 0.6;
        normal = 0.4;
        quente = 0;
        
    }
    else if ((14 < temp) && (temp <= 15))
    {
        frio = 0.5;
        normal = 0.5;
        quente = 0;
        
    }
    else if ((15 < temp) && (temp <= 16))
    {
        frio = 0.5;
        normal = 0.5;
        quente = 0;
        
    }
    else if ((16 < temp) && (temp <= 17))
    {
        frio = 0.4;
        normal = 0.6;
        quente = 0;
        
    }
    else if ((17 < temp) && (temp <= 18))
    {
        frio = 0.3;
        normal = 0.7;
        quente = 0;
        
    }
    else if ((18 < temp) && (temp <= 19))
    {
        frio = 0.2;
        normal = 0.8;
        quente = 0;
        
    }
    else if ((19 < temp) && (temp <= 20))
    {
        frio = 0.1;
        normal = 0.9;
        quente = 0;
        
    }
    else if ((20 < temp) && (temp <= 25))
    {
        frio = 0;
        normal = 1;
        quente = 0;
        
    }
    else if ((25 < temp) && (temp <= 26))
    {
        frio = 0;
        normal = 0.9;
        quente = 0.1;
        
    }
    else if ((26 < temp) && (temp <= 27))
    {
        frio = 0;
        normal = 0.8;
        quente = 0.2;
        
    }
    else if ((27 < temp) && (temp <= 28))
    {
        frio = 0;
        normal = 0.7;
        quente = 0.3;
        
    }
    else if ((28 < temp) && (temp <= 29))
    {
        frio = 0;
        normal = 0.6;
        quente = 0.4;
        
    }
    else if ((29 < temp) && (temp <= 30))
    {
        frio = 0;
        normal = 0.5;
        quente = 0.5;
        
    }
    else if ((30 < temp) && (temp <= 31))
    {
        frio = 0;
        normal = 0.5;
        quente = 0.5;
        
    }
    else if ((31 < temp) && (temp <= 32))
    {
        frio = 0;
        normal = 0.4;
        quente = 0.6;
        
    }
    else if ((32 < temp) && (temp <= 33))
    {
        frio = 0;
        normal = 0.3;
        quente = 0.7;
        
    }
    else if ((33 < temp) && (temp <= 34))
    {
        frio = 0;
        normal = 0.2;
        quente = 0.8;
        
    }
    else if ((34 < temp) && (temp <= 35))
    {
        frio = 0;
        normal = 0.1;
        quente = 0.9;
        
    }
    else if (temp > 35)
    {
        frio = 0;
        normal = 0;
        quente = 1;
        
    }

    if ((frio > quente) && (normal != 1))
    {
        printf("\nO aparelho está aquecendo com %.0f%% de potência\n\n", frio * 100);
    }
    else if ((quente > frio) && (normal != 1))
    {
        printf("\nO aparelho está resfriando com %.0f%% de potência\n\n", quente * 100);
    }
    else if (normal == 1)
    {
        printf("\nO aparelho está desligado\n\n");
    }

    return 0;
}
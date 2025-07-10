

#include <stdio.h>
#include <stdlib.h>  


int main() 
{
    int temperaturasOutubro[31], i,somaTemperatura = 0, diaInferior = 0;
    float media;

    for (i = 0; i < 31; i++) 
    {
        printf("Digite as temperaturas:  ");
        scanf_s("%i", &temperaturasOutubro[i]);
        somaTemperatura += temperaturasOutubro[i];
    }

    media = somaTemperatura / i;
    printf("A temperatura media e:  %.2f\n", media);
    
    for (i = 0; i < 31; i++)
    {
        if (temperaturasOutubro[i] < media)
        {
            diaInferior++;
        }
    }
    for (i = 0; i < 31; i++)
    {
        if (temperaturasOutubro[i] > media)
        {
            printf("Temperatura maior que a media no dia %i = %i Graus Celsius\n\n",i, temperaturasOutubro[i]);
        }
    }
    printf("Quantidade de dias com a temperatura inferior a media:  %i\n", diaInferior);
    
    system("pause");
}

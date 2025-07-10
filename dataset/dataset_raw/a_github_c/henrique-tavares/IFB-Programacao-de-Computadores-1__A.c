#include <stdio.h>
#define true 1
#define false 0

int main()
{
    int n,num,aux,condicao = true, maior, smaior, smenor, menor, maior0, smaior0, menor0, smenor0;

    scanf ("%i", &n);

    for (int i=0; i<n; i++)
    {
        scanf ("%i", &num);
        if (i==0)
        {
            maior = num;
            menor = num;
            smaior = num;
            smenor = num;
        }
        else
        {
            if (num > maior)
            {
                aux = maior;
                maior = num;
                smaior = aux;
            }
            else if (num < menor)
            {
                aux = menor;
                menor = num;
                smenor = aux;
            }
            if ((maior == smaior)&&(num < smaior)&&(num > smenor)&&(num > menor))
            {
                smaior = num;
            }
            else if ((menor == smenor)&&(num > smenor)&&(num < smaior)&&(num < maior))
            {
                smenor = num;
            }
            else if ((maior == smaior)&&(num < smaior))
            {
                smaior = num;
            }
            else if ((menor == smenor)&&(num > smenor))
            {
                smenor = num;
            }
            if ((maior == smaior)&&(maior == smenor)&&(num < smenor)&&(num > menor))
            {
                smaior = num;
                smenor = num;
            }
            else if ((menor == smenor)&&(menor == smaior)&&(num > smaior)&&(num < maior))
            {
                smenor = num;
                smaior = num;
            }
            if ((num < maior)&&(num > smaior))
            {
                smaior = num;
            }
            else if ((num > menor)&&(num < smenor))
            {
                smenor = num;
            }
        }
        
    }
    
        if ((maior == smaior)&&(smaior == smenor)&&(smenor == menor))
            printf ("%i\n%i\nnao definido\nnao deifnido\n", maior, menor);

        else
            printf ("%i\n%i\n%i\n%i\n", maior, menor, smaior, smenor);
    
    return 0;
}
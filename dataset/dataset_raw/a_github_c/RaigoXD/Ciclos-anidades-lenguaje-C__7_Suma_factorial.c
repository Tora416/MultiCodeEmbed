
#include <stdio.h>

int factorial(int num)
{
    if(num == 1)
        return 1;
    else
        return num * factorial(num - 1);
}

int Suma(int numero, int sumatoria);



int main()
{
    int numero = 0;
    printf("Programa calcula la suma de 0 hasta un numero N ingresado por el usuario\nIngresa un numero:");
    scanf("%i",&numero);

    if(numero == 0)
        printf("La suma de los factoriales de 0 es 1");
    else
        printf("La suma de los factoriales de %i es %i",numero,Suma(numero,0));

    return 0;
}

int Suma(int numero, int Sumatoria)
{
    if(numero >= 1){
        Sumatoria += factorial(numero);
        Suma(--numero, Sumatoria);  
    }else{
        return Sumatoria + 1;
    }
}

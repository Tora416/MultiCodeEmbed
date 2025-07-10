
#include <stdio.h>

double Exp(int numero, int exponente)
{
    double Total = 1;
    int i = 0;
    while(i < exponente)
    {
    Total *= numero;
    ++i;
    }
    return Total;
}


int main()
{
    int X = 0;
    int veces = 0;
    printf("\nPrograma para calcular ln(x) mediante sumas de Taylor\nIngresa X:");
    scanf("%i", &X);
    printf("\nIngrse el numero de sumas: ");
    scanf("%i", &veces);
    double Suma_total = 0.0;
    int i=1;
    while(i <= veces){
        if(i%2 == 0)
            Suma_total += Exp(X-1, i+1) / (i+1);
        else
            Suma_total -= Exp(X-1, i+1) / (i +1);
        ++i;
    }
    printf("ln(%i) es igual a %lf", X, (Suma_total + (X - 1)));

    return 0;
}
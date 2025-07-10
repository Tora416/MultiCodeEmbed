
#include <stdio.h>
double Fac(int N)
{
    double Factorial = 1.0;
    for(int i = 1;i < N; Factorial *= ++i);
    return Factorial;
}
double Exp(int numero, int exponente)
{
    double Total = 1;
    for(int i = 0; i < exponente; ++i)
    {
        Total *= numero;
    }
    return Total;
}


int main()
{
    int X = 0;
    int veces = 0;
    printf("\nPrograma para calcular sen(X) mediante sumas de Taylor\nIngresa X:");
    scanf("%i", &X); 
    printf("\nIngrse el numero de sumas: ");
    scanf("%i", &veces);
    double Suma_total = 0.0;
    for(int i = 1; i <= veces; ++i){
        if(i%2 == 0)
            Suma_total += Exp(X, (i*2)+1) / Fac((i*2)+1);
    else
        Suma_total -= Exp(X, (i*2)+1) / Fac((i*2)+1);
    }
    printf("sen(%i) es igual a %lf", X, (Suma_total + X));

    return 0;
}


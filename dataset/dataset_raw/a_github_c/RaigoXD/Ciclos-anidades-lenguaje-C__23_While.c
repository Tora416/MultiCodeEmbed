
#include <stdio.h>
double Fac(int N)
{
    double Factorial = 1.0;
    int i = 1;
    while(i < N){Factorial *= ++i;}
    return Factorial;
}
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
    printf("\nPrograma para calcular Cosh(x) mediante sumas de Taylor\nIngresa X:");
    scanf("%i", &X);
    printf("\nIngrse el numero de sumas: ");
    scanf("%i", &veces);
    double Suma_total = 0.0;
    int i=1;
    while(i <= veces){
        Suma_total += Exp(X,(i*2)) / Fac((i*2));
        ++i;
    }
    printf("Cosh(%i) es igual a %lf", X, (Suma_total + 1));

    return 0;
}
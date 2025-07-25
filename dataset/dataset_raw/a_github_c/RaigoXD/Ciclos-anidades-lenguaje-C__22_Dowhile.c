
#include <stdio.h>
double Fac(int N)
{
    double Factorial = 1.0;
    int i = 1;
    do{Factorial *= ++i;}while(i < N);
    return Factorial;
}
double Exp(int numero, int exponente)
{
    double Total = 1;
    int i = 0;
    do{
    Total *= numero;
    ++i;
    }while(i < exponente);
    return Total;
}


int main()
{
    int X = 0;
    int veces = 0;
    printf("\nPrograma para calcular Senh(x) mediante sumas de Taylor\nIngresa X:");
    scanf("%i", &X);
    printf("\nIngrse el numero de sumas: ");
    scanf("%i", &veces);
    double Suma_total = 0.0;
    int i=1;
    do{
        Suma_total += Exp(X,(i*2)+1) / Fac((i*2)+1);
        ++i;
    }while(i <= veces);
    printf("senh(%i) es igual a %lf", X, (Suma_total + X));

    return 0;
}
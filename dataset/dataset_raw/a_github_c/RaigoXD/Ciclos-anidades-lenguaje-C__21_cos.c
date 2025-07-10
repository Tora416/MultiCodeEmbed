
#include <stdio.h>

double Fac(double num) 
{
        if(num == 1)
                return 1;
        else
                return num * Fac(num - 1);
}

double Exp(int Exponente, double numero)
{
        if(Exponente == 1){
                return numero;
        }else{
                return numero * Exp(--Exponente, numero);
        }
}




void cos(int contador,int iteraciones, double suma, double X);


int main()
{
        double X;
    int  I;
        printf("Programa para calcular cos(X) mediante sumas de taylor \nIngresa X: ");
        
    scanf("%lf", &X);
    
    cos(1,50,0,X); 
        return 0;
}

void cos(int contador, int iteraciones, double suma, double X)
{
    if(contador <= iteraciones){    
        if(contador%2 == 0){
            printf("\n%i -> %lf / %0.0lf = %0.6lf", contador, Exp(contador*2,X), Fac(contador * 2), Exp(contador*2,X) / Fac(contador * 2));

            suma = suma + (Exp(contador*2,X) / Fac(contador * 2));
            printf("   Suma Actual: %lf", suma);
            cos(++contador, iteraciones,suma,X);
        }else{
            printf("\n%i -> %lf / %0.0lf = %0.6lf", contador, Exp(contador*2,X), Fac(contador * 2), Exp(contador*2,X) / Fac(contador * 2));
            suma = suma - (Exp(contador*2,X) / Fac(contador * 2));
            printf("  Suma Actual: %lf", suma);
            cos(++contador, iteraciones,suma,X);
        }
    }else{
        printf("\nCos(%lf) es igual a: %lf", X, (suma + 1));
    }
}


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





void cosh(int contador, int iteraciones, double total, double X);


int main(){

        double X;
        printf("Programa para calcular el cosh(X) por medio de sumas de Taylor\nValor de X:");
        scanf("%lf", &X);
        cosh(1,30,0,X);
        return 0;
}

void cosh(int contador, int iteraciones, double total, double X)
{
        if(contador <= iteraciones){
                total = total + Exp((contador*2),X) / Fac((contador*2));
                cosh(++contador,iteraciones,total,X);
        }else{
                printf("\n**El cosh(%lf) es igual a: %lf",X,total+1);

        }
}


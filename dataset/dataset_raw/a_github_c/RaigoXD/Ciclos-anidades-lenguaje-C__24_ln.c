
#include <stdio.h>


double Exp(int Exponente, double numero)
{
        if(Exponente == 1){
                return numero;
        }else{
                return numero * Exp(--Exponente, numero);
        }
}





void ln(int contador, int iteraciones, double total, double X);

int main(){

        double X;
        printf("Programa para calcular el cosh(X) por medio de sumas de Taylor\nValor de X:");
        scanf("%lf", &X);
    if(X == 0.0){
        printf("Fuera de rango");
    }else{
            ln(1,10,0,X);
    }
    return 0;
}



void ln(int contador, int iteraciones, double total, double X)
{
    if(contador <= iteraciones){
        if(contador%2 == 0){
            printf("+ %lf", (Exp(contador + 1, X-1) / (contador+1)));
            total = total + (Exp(contador + 1, X-1) / (contador+1));
            
            ln(++contador,iteraciones,total,X);
        }else{
                        printf("- %lf",(Exp(contador + 1, X-1) / (contador+1)));
                        total = total - (Exp(contador + 1, X-1) / (contador+1));
            
                        ln(++contador,iteraciones,total,X);
                }
    }else{
        printf("\n\n\n**El ln(%lf) es %lf", X, total + (X -1));
    }
}


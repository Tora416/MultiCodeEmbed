
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





void Senh(int contador, int iteraciones, double total, double X);


int main(){
    
    double X;
    printf("Programa para calcular el senh(X) por medio de sumas de Taylor\nValor de X:");
    scanf("%lf", &X);
    Senh(1,30,0,X);
    return 0;
}

void Senh(int contador, int iteraciones, double total, double X)
{
    if(contador <= iteraciones){
        total = total + Exp((contador*2)+1,X) / Fac((contador*2)+1);
        Senh(++contador,iteraciones,total,X);
    }else{
        printf("\n**El Senh(%lf) es igual a: %lf",X,total+X);

    }
}


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




void Sen(int contador, int iteraciones, double total, double X);


int main(){
        double X;
        printf("Programa para calcular el sen(X) por medio de sumas de Taylor\nValor de X:");
        scanf("%lf", &X);
        Sen(1,50,0,X);
        return 0;
}

void Sen(int contador, int iteraciones, double total, double X)
{
        if(contador <= iteraciones){
        if(contador%2 == 0){
            total = total + (Exp((contador*2)+1, X) / Fac((contador*2)+1));
            Sen(++contador, iteraciones,total,X);
        }else{
            total = total - (Exp((contador*2)+1, X) / Fac((contador*2)+1));
                        Sen(++contador, iteraciones,total,X);
        }
        }else{
                printf("\n**El Sen(%lf) es igual a: %lf",X,total+X);
        }
}

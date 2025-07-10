
#include <stdio.h>

void Multipli(int numero, int contador)
{
    if(contador <= 10){
        printf("\n%i X %i = %i", numero, contador, numero*contador);
        Multipli(numero, ++contador);
    }

}


void Tablas(int numero)
{
    if(numero <= 10){
        printf("\n*** Tabla del %i ***", numero);
        Multipli(numero, 1);
        Tablas(++numero);
    }else{
        printf("\n***Fin del ciclo***");
    }
}

int main()  
{
    printf("\nEste programa Muestra todas las tablas de multiplicar de base 10\n");
    Tablas(1);
    return 0;
}

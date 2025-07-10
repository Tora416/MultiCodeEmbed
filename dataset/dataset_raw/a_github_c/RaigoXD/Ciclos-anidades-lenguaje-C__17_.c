
#include <stdio.h>

void Columnas(int contador, int pibote);
void Filas(int contador);


int main()
{
    Filas(1);
    return 0;

}
void Columnas(int contador, int pibote){
    if(contador <= 19){
        if(contador == (1 + pibote) || contador == (19 - pibote))
            printf("Z");
        else
            printf(" ");
        Columnas(++contador, pibote);
    }

}

void Filas(int contador)
{
    if(contador < 11){
        Columnas(1, (contador - 1));
        printf("\n");
        Filas(++contador);      
    }
}

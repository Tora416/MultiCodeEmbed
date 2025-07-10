
#include <stdio.h>

void Columnas(int contador, int pibote);
void Filas(int contador);

int main()
{
    Filas(1);
    return 0;
}

void Columnas(int contador, int pibote)
{
    if(contador < 80){
        if(contador > (80 - pibote))
            printf("A");
        else
            printf(" ");
        Columnas(++contador,pibote);
    }
}

void Filas(int contador)
{
    if(contador < 25){
        Columnas(1, contador);
        printf("\n");
        Filas(++contador);
    }
}

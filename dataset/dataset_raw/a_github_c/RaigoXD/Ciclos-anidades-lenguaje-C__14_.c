
#include <stdio.h>

void Columna(int contador, int pibote);
void Filas(int contador);

int main()
{
        Filas(1);
        return 0;
}

void Columnas(int contador, int pibote){
    if(contador <= 13){
        if(contador >= (1 + pibote) && contador <= (13 - pibote))
                        printf("P");
                else
                        printf(" ");
                Columnas(++contador, pibote);
        }
}

void Filas(int contador)
{
        if(contador < 8){
                Columnas(1, (contador-1));
                printf("\n");
                Filas(++contador);
        }
}

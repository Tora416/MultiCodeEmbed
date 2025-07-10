
#include <stdio.h>

void Columnas(int contador, int pibote);
void Filas(int contador, int contador2);

int main()
{
    
    Filas(1, 7);
    return 0;
}

void Columnas(int contador, int pibote)
{
    if(contador <= 34){
        if(contador >= 28){
            if(contador >= (28 + pibote) && contador <= (34 - pibote))
                printf(" ");
            else
                printf("A");
            Columnas(++contador, pibote);
        }else{
            printf(" ");
            Columnas(++contador, pibote);
        }
    }
}


void Filas(int contador, int contador2)
{
    printf("\n");
    if(contador < 8){
        if(contador >= 4){
            Columnas(1,contador2);
            Filas(++contador,--contador2);

        }else{
            Columnas(1,contador);
            Filas(++contador, --contador2);
        }
    }
}



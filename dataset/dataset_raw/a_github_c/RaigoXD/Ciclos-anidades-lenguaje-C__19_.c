
#include <stdio.h>

void Columnas();
void Filas();

int main()
{

    Filas(0, 10);
    return 0;

}

void Columnas(int contador, int pibote)
{
    if(contador <= 40){
        if(contador >= 40 - pibote)
            printf("A");
        else
            printf(" ");
        Columnas(++contador,pibote);
    }
}


void Filas(int contador, int contador2)
{
    printf("\n");
    if(contador < 11){
        if(contador > 5){
            Columnas(1,contador2);
            Filas(++contador, --contador2);
        }else{
            Columnas(1,contador);
            Filas(++contador,--contador2);
        }
    }
}

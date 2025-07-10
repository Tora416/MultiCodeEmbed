
#include <stdio.h>

void Columnas(int contador, int pibote);
void Filas(int contador1,int contador2);


int main()
{
    Filas(1,7);
    return 0;
}

void Columnas(int contador, int pibote)
{
    if(contador <= 20){
        if(contador >= (10 - pibote) && contador <= (10 + pibote))
            printf("Z");
        else
            printf(" ");
        Columnas(++contador, pibote);
    }

}

void Filas(int contador1, int contador2)
{
    printf("\n");
    if(contador1 < 8){
        if(contador1 > 4){
            Columnas(1, (contador2 - 1));
            Filas(++contador1, --contador2);
        }else{
            Columnas(1,( contador1 - 1));
            Filas(++contador1, --contador2);
        }
    }
}

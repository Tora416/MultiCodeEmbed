
#include <stdio.h>

void Columna(int contador, int pibote, char letra_c);
void Filas(int contador);

int main()
{
    Filas(0);
    return 0;
}

void Columna(int contador, int pibote, char letra_A){
    if(contador <= 13){
        if(contador >= (1 + pibote) && contador <= (13 - pibote))
            printf("%c", letra_A);
        else
            printf(" ");
        Columna(++contador,pibote,letra_A);
    }
}

void Filas(int contador){
    if(contador < 7){
        switch (contador){
            case 0: Columna(1,contador,'P');break;
            case 1: Columna(1,contador,'N');break;
            case 2: Columna(1,contador,'L');break;
            case 3: Columna(1,contador,'J');break;
            case 4: Columna(1,contador,'H');break;
            case 5: Columna(1,contador,'F');break;
            case 6: Columna(1,contador,'D');break;
        }
        printf("\n");
        Filas(++contador);
    }
}





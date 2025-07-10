
#include <stdio.h>

void Columna(int pibote)
{
    for(int i = 1; i <= 34; ++i)
    {
    if(i >= 28){
        if(i >= (28 + pibote) && i <= 34 - pibote){
        printf(" ");
        }else{
        printf("A");
        }
    }else{
        printf(" ");
    }
    }
}


int main()
{
    int contador1 = 1;
    int contador2 = 7;
    for(contador1 = 1; contador1 < 8; ++contador1)
    {
    printf("\n");
        if(contador1 >= 4)
        Columna(contador2);
    else
        Columna(contador1);
        --contador2;
    }
}



#include <stdio.h>

void Columna(int pibote)
{
    int i = 1;
    do
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
        ++i;
    }while(i <= 34);
}


int main()
{
    int contador1 = 1;
    int contador2 = 7;
    do
    {
        printf("\n");
            if(contador1 >= 4)
            Columna(contador2);
        else
            Columna(contador1);
        
        --contador2;
        ++contador1;
    }while(contador1 < 8);
}
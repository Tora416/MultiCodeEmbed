
#include <stdio.h>
#include <stdlib.h> 
#include <unistd.h> 

void mostrar(int X_1, int X_2, int contador);

int main()
{
    system("cls"); 
    int contador = 0;
    int X_1 = 1;
    int X_2 = 80;
    for(contador =1; X_1 != 41; ++contador){
        if(contador <= 80){
            if(contador == X_1)
                printf("X");
            else if(contador == X_2)
                printf("X");
            else
                printf(" ");
         }else{
             sleep(0.4);
             system("cls");
             ++X_1;
         --X_2;
        contador = 1;
         }
    }
        return 0;
}

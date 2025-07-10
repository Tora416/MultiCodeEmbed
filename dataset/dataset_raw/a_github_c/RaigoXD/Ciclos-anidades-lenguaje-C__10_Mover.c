
#include <stdio.h>
#include <stdlib.h> 
#include <unistd.h> 

void mostrar(int X_1, int X_2, int contador);

int main()
{
    system("cls"); 
    mostrar(1,80,1);
    return 0;
}

void mostrar(int X_1, int X_2, int contador)
{
    if(X_1 != 41){
        if(contador <= 80){
            if(contador == X_1)
                printf("X");
            else if(contador == X_2)
                printf("X");
            else
                printf(" ");
            mostrar(X_1,X_2, ++contador);
        }else{
            sleep(0.4);
            system("cls");
            mostrar(++X_1, --X_2, 1);
        }
    }   
}

#include <stdio.h>

void fibonacci(int posicion){
    
    long int i;
    unsigned long int actual = 0, siguiente = 1, temporal;
    for(i =0; i < posicion; i++){
        printf("%ld, ", actual);
        temporal = siguiente;
        siguiente = siguiente + actual;
        actual = temporal;
    }
}

int fibonacci_recursivo(int posicion){
    if (posicion == 0)
        return 0;
    if (posicion == 1)
        return 1;
    if (posicion == 2)
        return 1;
    else
        return fibonacci_recursivo(posicion - 1) + fibonacci_recursivo(posicion - 2);
}

int main(){
    printf("fiboniacci iterativo:");
    fibonacci(6);
    printf("\n%d \n", fibonacci_recursivo(5));
    return 0;
}
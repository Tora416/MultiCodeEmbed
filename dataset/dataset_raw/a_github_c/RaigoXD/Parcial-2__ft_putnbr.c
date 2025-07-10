
#include <stdio.h>

void ft_putnbr(int );
void ft_putnbr(int numero){
    int negativo = 0;

    if(numero < 0){
        numero = numero*(-1);
        negativo = 1;
    }
    else
        negativo = 0;
    
    int longitud_N = 0; 
    for(int  i = numero; i > 0; i= i/10){
        ++longitud_N; 
    }

    if(negativo)
        longitud_N++;

    char string_intermedio[11] = " "; 

    for(int i = numero; i > 0; i = i/10){ 
        string_intermedio[longitud_N-1] = (i%10)+48;
        --longitud_N;
    }
    if(negativo)
        string_intermedio[0] = '-';


    printf("%s", string_intermedio); 
}

int main()
{
    ft_putnbr(-204);
    return 0;
}
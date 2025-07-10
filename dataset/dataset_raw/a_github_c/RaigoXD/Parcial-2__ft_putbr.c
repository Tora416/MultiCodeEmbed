
#include <stdio.h>

int longitud_N(int numero, int contador){
    if(numero > 0){
        longitud_N(numero/10, contador + 1);
    }else{
        return contador;
    }
}

void llenar_string(char *str, int numero, int longitud_N){
    if(numero > 0){
        str[longitud_N - 1] = (numero%10)+48;
        llenar_string(str, numero/10, longitud_N-1);
    }
}


void ft_putnbr(int );
void ft_putnbr(int numero){
    int longitud = longitud_N(numero, 0);
    int negativo = 0;
    char string_intermedio[11] = "";

    if(numero < 0){
        numero = numero*(-1);
        longitud++;
        llenar_string(string_intermedio, numero, longitud);
        string_intermedio[0] = '-';
    }else{
        llenar_string(string_intermedio, numero, longitud);
    }
    printf("%s", string_intermedio);
}

int main()
{
    ft_putnbr(123);
    return 0;
}
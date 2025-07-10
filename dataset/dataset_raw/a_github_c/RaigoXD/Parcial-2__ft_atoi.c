
#include <stdio.h>
 int potencia(int, int);
 int potencia(int numero, int exponente){
    int resultado = 1;
    if(exponente == 0)
        return 1;
    else{
        for(int i = 1; i <= exponente; i++) resultado *= numero;
        return resultado;
    }
 }

int atoi(char *str);
int atoi(char *str){
    int longitud = 0;
    int Valores = 0;
    int Total = 0;
    for( longitud = 0; str[longitud] != '\0'; ++longitud);
    for(int i = 0; i < longitud; i++){
        Valores = ((int)(str[i]) - 48) * potencia(10, (longitud - i - 1));
        Total += Valores;
    }
    return Total;
}


int main(){

    char palabra[10] = "23456";
    int value = 0;
    value = atoi(palabra);
    printf("%i", value );
    return 0;
}
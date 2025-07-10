#include <stdio.h>
#include <stdlib.h>

void leer_calorias(int a[], int tam);
float promedio_calorias(int a[], int tam);

int main(){

    int *calorias = NULL;
    char respuesta;
    int posicion = 1;

    calorias = (int *) malloc ( posicion * sizeof(int));

    do {
        calorias = (int *) realloc (calorias, posicion);
        leer_calorias(calorias, posicion);
        posicion++;
        printf("Desea agregar consumo de calorias de otro día?");
        fflush(stdin);
        respuesta = getchar();  
    } while(respuesta != 'n');

    printf("El promedio de calorías consumidas en %d días fue %.2f\n"
        , posicion - 1
        , promedio_calorias(calorias, posicion - 1));
        
    free(calorias);
    
    return 0;
}

void leer_calorias(int a[], int posicion){
    printf("Ingrese las calorias consumidas en el dia: ");
    scanf("%d", &a[posicion - 1]);
}

float promedio_calorias(int a[], int tam){
    int suma = 0;
    for (int i = 0; i < tam; i++){
        suma += a[i];
    }
    return (suma/tam);
}
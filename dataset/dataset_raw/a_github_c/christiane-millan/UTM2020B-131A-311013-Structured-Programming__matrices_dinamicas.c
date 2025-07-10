#include <stdio.h>
#include <stdlib.h>

void leer_temperaturas(float **t, int f, int c);
void mostrar_temperaturas(float **t, int f, int c);

int main() {
    
    float **temperaturas = NULL;
    int tamanno_filas, frecuencia, tamanno_columnas;

    printf("Ingrese la cantidad de días que se registrarán tempereraturas:");
    scanf("%d", &tamanno_filas);
    printf("Ingrese cada cuanta horas se registrarán temperatural por día");
    scanf("%d", &frecuencia);
    tamanno_columnas = 24 / frecuencia; 

    temperaturas = (float **) malloc (tamanno_filas * sizeof(float *));
    if( temperaturas == NULL){
        printf("No se reservo la memoria");
        return -1;
    }

    for (int i = 0; i < tamanno_filas; i++) {
        temperaturas[i] = (float *) malloc (tamanno_columnas * sizeof(float));
        if(temperaturas[i] == NULL){
            printf("No se reervó la memoria");
            return -1;
        }
    }

    leer_temperaturas(temperaturas, tamanno_filas, tamanno_columnas);
    mostrar_temperaturas(temperaturas, tamanno_filas, tamanno_columnas);

    for (int i = 0; i < tamanno_columnas; i++){
        free(temperaturas[i]);
    }
    free(temperaturas);
    
    return 0;
}

void leer_temperaturas(float **t, int f, int c){
    for (int i = 0; i < f; i++){
        for (int j = 0; j < c; j++){
            printf("Ingrese la temperatura %d del dia %d:", j+1, i+1);
            scanf("%f", &t[i][j]);
        }
    }
}

void mostrar_temperaturas(float **t, int f, int c){
    for (int i = 0; i < f; i++){
        for (int j = 0; j < c; j++){
            printf("%f\t", t[i][j]);
        }
        printf("\n");
    }
    
}
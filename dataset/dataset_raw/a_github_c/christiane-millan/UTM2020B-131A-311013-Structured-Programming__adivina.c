#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define INI 1
#define FIN 1000

int generar_aleatorio(int inicio, int final);
int menu();
void jugar();


int main(void){
    srand(time(NULL));
    char respuesta = 'N';
    do {
        int op = menu();
        switch (op) {
        case 1: jugar();
            break;
        default:
            break;
        }
        printf("Deseas continuar jugando? [S]i o [N]o \n");
        fflush(stdin);
        scanf("%c", &respuesta);
    } while( respuesta == 'S');
    
    return 0;
}

int menu(){
    int opcion;
    system("clear");
    printf("Juedo de adivina un número.\n");
    printf("1. Jugar\n");
    printf("2. Salir\n");
    printf("Elije una opción:");
    scanf("%d", &opcion);
    return opcion;
}

int generar_aleatorio(int inicio, int final){
    return rand() % (final - inicio + 1) + inicio;
}

void jugar(){
    int alea = generar_aleatorio(INI, FIN);
    printf("Adivina el número entre %d - %d: ", INI, FIN);
    while(1) {
        int respuesta;
        
        scanf("%d", &respuesta);
        if( respuesta == alea){
            printf("Felicidades!!! Adivinaste...\n");
            printf("Presione una tecla para continuar...");
            fflush(stdin);
            getchar();
            break;
        } else {
            if( respuesta < alea){
                printf("El valor es más grande\n");
            } else {
                printf("El valor es más pequeño\n");
            }
        }
        printf("Intenta de nuevo adivinar el número entre %d - %d: ", INI, FIN);
    }
}
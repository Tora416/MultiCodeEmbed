#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define INICIO 1
#define FIN 1000

int aleatorio(int inicio, int fin);
void menu();
void jugar();

int main(void){
    srand(time(0));
    int opcion;

    while(1){
        menu();
        scanf("%d", &opcion);
        if(opcion == 1){
            jugar();
        } else 
            break;
    }
    return 0;
}

void jugar(){
    int respuesta;
    int numero = aleatorio(INICIO, FIN);
    int intentos = 1;
    system("clear");
    do {
        printf("Número de intentos: %d\n", intentos);
        printf("Adiviana un número entero entre [%d - %d]", INICIO, FIN);
        scanf("%d", &respuesta );
        intentos++;
        if(respuesta > numero) {
            printf("Número muy alto\n");
        } else {
            if (respuesta < numero)
                printf("Numero muy bajo\n");
            else{
                printf("Excelente!! Adivinaste el número!!\n");  
                fflush(stdin); 
                printf("Presiona una tecla para continuar...");
                getchar();
            }
        }
        
    } while (respuesta != numero );
}

void menu(){
    system("clear");
    printf("1. Iniciar juego.\n");
    printf("2. Salir\n\n");
    printf("Ingres una opción:");
}

int aleatorio(int inicio, int fin){
    return rand() % (fin - inicio + 1) + inicio;
}
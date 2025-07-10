#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>
#define MAX 100
#define MAX_ASISTENCIA 5
#define MAX_CALIFICACIONES 4
#define MAX_NOMBRE 60
#define MAX_ALUMNOS 4

struct estudiant_{
    int matricula;
    char nombre[MAX_NOMBRE];
    float calificaciones[MAX_CALIFICACIONES];
    int asistencias[MAX_ASISTENCIA];
};

typedef struct estudiant_ estudiante;
estudiante lista_estudiantes[MAX_ALUMNOS];


void imprimir_menu();
void agregar_alumno();
void modificar_alumno();
void imprimir_alumno();
void imprimir_asistencias(const int posicion);
void imprimir_menu_calificaciones();
void menu_modificacion_calificaciones();
void imprimir_alumnos_en_tabla();
void imprimir_alumno_por_fila(int posicion);

int posicion_alumno();
void pase_asistencia();
float promedio(float *c);
float minimo(float *c);
float maximo(float *c);

int siguiente_alumno = 0;

int main(){
    int opcion;
    while (1) {
        imprimir_menu();
        scanf("%d", &opcion);
        switch (opcion) {
            case 1: agregar_alumno();
                break;
            case 2: modificar_alumno();
                break;
             case 3: menu_modificacion_calificaciones();
                 break;
            case 4: imprimir_alumno();
                 break;
            case 5: imprimir_alumnos_en_tabla();
                break;
            case 6: pase_asistencia();
                 break;
            case 7:
                return 0;
                break;
            default:
                break;
        }
    }
    return 0;
}

void imprimir_menu(){
    char mensaje[MAX] = "SISTEMA DE CONTROL DE CALIFICACIONES";
    system("clear");
    printf("----------------------------------------------\n");
    printf("%s\n", mensaje);
    printf("----------------------------------------------\n");
    printf("Menu de opciones\n");
    printf("----------------------------------------------\n");
    printf("1. Agregar alumno\n");
    printf("2. Modificar alumno\n");
    printf("3. Modificar calificaciones\n");
    printf("4. Imprimir datos del alumno\n");
    printf("5. Lista de alumnos\n");
    printf("6. Pase de lista\n");
    printf("7. Salir\n");
    printf("Ingresa una opción: \n");
}

void agregar_alumno(){
    if(siguiente_alumno == MAX_ALUMNOS){
        printf("No se puede agregar nuevo alumno, espacio insuficiente...");
        puts("Presiona cualquier tecla para continuar...");
        fflush(stdin);
        getchar();
    } else {
        estudiante nuevo_alumno;
        printf("Ingresa la matrícula:");
        scanf("%d", &nuevo_alumno.matricula);
        fflush(stdin);
        printf("Ingresa el nombre del alumno:");
        fgets(nuevo_alumno.nombre, 60, stdin);
        nuevo_alumno.calificaciones[0] = 0.0;
        nuevo_alumno.calificaciones[1] = 0.0;
        nuevo_alumno.calificaciones[2] = 0.0;
        nuevo_alumno.calificaciones[3] = 0.0;
        puts("Datos almacenado correctamente...");
        puts("Presiona cualquier tecla para continuar...");
        fflush(stdin);
        getchar();
        lista_estudiantes[siguiente_alumno] = nuevo_alumno;
        siguiente_alumno++;
    } 
}

void modificar_alumno(){
    system("clear");
    puts("\tMenu para cambio de nombre...");
    int posicion = posicion_alumno();
    estudiante estudiante_seleccionado = lista_estudiantes[posicion];
    printf("El nombre del alumno es: %s\n", estudiante_seleccionado.nombre);
    printf("Ingresa el nuevo nombre: ");
    fflush(stdin);
    fgets(estudiante_seleccionado.nombre, 60, stdin);
    lista_estudiantes[posicion] = estudiante_seleccionado;
}

int posicion_alumno(){
    int posicion;
    printf("\nIngresa la posicion [1 -  %d]: ", MAX_ALUMNOS);
    scanf("%d", &posicion);
    posicion--;
    return posicion;
}

void imprimir_alumno(){
    int posicion = posicion_alumno();
    
    printf("Matrícula: %d\n", lista_estudiantes[posicion].matricula);
    printf("Nombre del alumno: %s\n", lista_estudiantes[posicion].nombre);
    printf("Calificación 1: %.2f\n", lista_estudiantes[posicion].calificaciones[0]); 
    printf("Calificación 2: %.2f\n", lista_estudiantes[posicion].calificaciones[1]); 
    printf("Calificación 3: %.2f\n", lista_estudiantes[posicion].calificaciones[2]); 
    printf("Calificación f: %.2f\n", lista_estudiantes[posicion].calificaciones[3]); 
    float prom = promedio(lista_estudiantes[posicion].calificaciones);
    printf("Promedio : %.2f\n", prom);
    float m;
    m = minimo(lista_estudiantes[posicion].calificaciones);
    printf("Calificación mínima: %.2f\n", m);
    m = maximo(lista_estudiantes[posicion].calificaciones);
    printf("Calificación máxima: %.2f\n", m);
    imprimir_asistencias(posicion);
    fflush(stdin);
    getchar();
}

float promedio(float *c){
    float prom;
    float acumulador = 0.0;
    for (int i = 0; i < MAX_CALIFICACIONES - 1; i++)
    {
        acumulador += c[i];
    }
    prom = acumulador / MAX_CALIFICACIONES - 1;
    prom = (prom + c[MAX_CALIFICACIONES - 1]) / 2;
    return prom;
}

float minimo(float *c){
    float min = c[0];
    for (int i = 1; i < MAX_CALIFICACIONES; i++){
        if (min > c[i]){
            min = c[i];
        }
    }
    return min;
}

float maximo(float *c){
    float max = c[0];
    for (int i = 1; i < MAX_CALIFICACIONES; i++){
        if (max < c[i]){
            max = c[i];
        }
    }
    return max;
}

void imprimir_asistencias(const int posicion){
    printf("Asistencias: ");
    for (int i = 0; i < MAX_ASISTENCIA-1; i++)
    {
        if (lista_estudiantes[posicion].asistencias[i] == 1)
            printf("%s", "A, ");    
        else 
            printf("%s", "F, ");         
    }
    (lista_estudiantes[posicion].asistencias[MAX_ASISTENCIA-1] == 1)?printf("%s", "A"):printf("%s", "F");
    printf("\n");
}

void imprimir_menu_calificaciones(){
    printf("1. Modificar calificación 1:\n");
    printf("2. Modificar calificación 2:\n");
    printf("3. Modificar calificación 3:\n");
    printf("4. Modificar calificación f:\n");
    printf("5. Salir:\n");
    printf("Ingresa una opción:");
}

void menu_modificacion_calificaciones(){
    int opt = 0;
    int posicion = posicion_alumno();
    while(opt != 5) {
        imprimir_menu_calificaciones();
        scanf("%d", &opt);
        if (opt < MAX_CALIFICACIONES + 1) {
            printf("La calificación actual es: %f\n", 
                lista_estudiantes[posicion].calificaciones[opt-1]);
            printf("Ingresa nueva calificación %d:", opt-1);
            scanf("%f", &lista_estudiantes[posicion].calificaciones[opt-1]);
        }
    }
}

void pase_asistencia(){
    int dia;
    printf("Pase de asistencia...\n");
    int posicion = posicion_alumno();
    printf("Indicar dia de asistencia [1 - %d]: ", MAX_ASISTENCIA);
    scanf("%d", &dia);
    printf("[0]=Falta o [1]=Asistencia: ");
    scanf("%d", &lista_estudiantes[posicion].asistencias[dia - 1]);
}

void imprimir_alumnos_en_tabla(){
    system("clear");
    printf("----------------------------------------------\n");
    printf("Matricula\tNombre\t 1er\t2o\t3er\t Ord\n");
    printf("----------------------------------------------\n");
    for (int i = 0; i < siguiente_alumno; i++){
        imprimir_alumno_por_fila(i);
    }
    puts("Presione una tecla para continuar...");
    fflush(stdin);
    getchar();
}

void imprimir_alumno_por_fila(int posicion){
    printf("%d\t\t%s\t", lista_estudiantes[posicion].matricula, lista_estudiantes[posicion].nombre);
    for (int i = 0; i < MAX_CALIFICACIONES; i++){
        printf("%.2f\t", lista_estudiantes[posicion].calificaciones[i]);
    }
    printf("\n");
}
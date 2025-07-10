#include <stdio.h>

#define MAX_ALUMNO 60
#define MAX_CALIFICACIONES 4
#define MAX_ASISTENCIA 5

struct estudiante{
    int matricula;
    char nombre[MAX_ALUMNO];
    float calificaciones[MAX_CALIFICACIONES];
    int asistencias[MAX_ASISTENCIA];
} e5 = {345, "Karla Ramirez", {0.0, 0.0, 0.0, 0.0}, {0, 0, 0, 0, 0}};

struct estudiante e1, e2, e3;
struct estudiante e6;
struct estudiante e4 = { 123, "Juan Carlos", {0.0 , 0.0, 0.0, 0.0}, {0, 0, 0, 0, 0} };




int main(){
    int x1 = 1;
    int x2, x3, x4, x5 = 10;
    int numeros[] = {1, 2, 3, 4};
    x2 = x1; 

    printf("Ingresa la matricula:");
    scanf("%d", &e1.matricula);
    printf("Ingresa el nombre:");
    
    fflush(stdin);
    fgets(e1.nombre, MAX_ALUMNO, stdin);

    for (int i = 0; i < MAX_CALIFICACIONES; i++){
        printf("Ingresa calificacion %d: ", i + 1);
        scanf("%f", &e1.calificaciones[i]);   
    }

    for (int i = 0; i < MAX_ASISTENCIA; i++){
        printf("Ingresa asistencia del día %d: ", i + 1);
        scanf("%d", &e1.asistencias[i]);   
    }
    

    printf("\n\nDatos del alumno capturado:\n");
    printf("Matricula: %d\n", e1.matricula);
    printf("Nombre: %s\n", e1.nombre);
    for (int i = 0; i < MAX_CALIFICACIONES; i++){
        printf("Califación %d: %f\n", i+1, e1.calificaciones[i]);
    }
    for (int i = 0; i < MAX_ASISTENCIA; i++){
        printf("Asistencias %d: %d\n", i+1, e1.asistencias[i]);
    }

    char mensaje[] = "hola";
    mensaje = "hola mundo";
    strcpy(mensaje, "hola mundo");

    e2 = e1;
    
    e3.matricula = 456;
    
    strcpy(e3.nombre, "Juan Carlos");
    e3.calificaciones[0] = 10.0;
    e3.calificaciones[1] = 10.0;
    e3.calificaciones[2] = 10.0;
    e3.calificaciones[3] = 10.0;
    e3.asistencias[0] = 1;
    e3.asistencias[4] = 1;

    int x = 7;
    int *p_num;

    p_num = &x;
    *p_num = 10;
    printf(x);
    int arreglo_numeros = {1, 2, 3, 4};
    int *arreglo;
    arreglo = &arreglo_numeros;
    arreglo[0] = 5;
    *(arreglo + 0) = 5;

    struct estudiante *p_e1;
    p_e1 = &e1;

    p_e1->matricula = 567;
    strcpy(p_e1->nombre, "Jose Garcia");
    p_e1->calificaciones[0] = 10.0;
    p_e1->calificaciones[1] = 10.0;
    p_e1->calificaciones[2] = 10.0;
    p_e1->calificaciones[3] = 10.0;
    p_e1->asistencias[0] = 1;

    return 0;
}
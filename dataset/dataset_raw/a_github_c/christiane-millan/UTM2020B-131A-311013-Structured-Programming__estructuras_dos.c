#include <stdio.h>
#include <string.h>

#define MAX_ALUMNO 60
#define MAX_CALIFICACIONES 4
#define MAX_ASISTENCIA 5

struct direccion{
    char calle[60];
    char numero_exterior[5];
    char numer_interior[5];
    char colonia[60];
    char municipio[60];
    char entidad[60];
    int cp;
};

typedef struct direccion mi_direccion;
typedef int mi_integercito;

struct estudiante{
    int matricula;
    char nombre[MAX_ALUMNO];
    mi_direccion direccion_estudiante;
    float calificaciones[MAX_CALIFICACIONES];
    int asistencias[MAX_ASISTENCIA];
};

typedef struct estudiante mi_estudiante;

struct estudiante e1;
mi_estudiante e2;
mi_integercito x1, x2, x3, x100;
int arreglo_x[100];

mi_estudiante lista_estudiantes[100];

int main(){

    e1.matricula = 123;
    strcpy(e1.nombre, "Juan Carlos");
    strcpy(e1.direccion_estudiante.calle, "Vicente Guerrero");
    strcpy(e1.direccion_estudiante.numer_interior, "2A");
    strcpy(e1.direccion_estudiante.numero_exterior, "234");
    strcpy(e1.direccion_estudiante.colonia, "Centro Historico");
    strcpy(e1.direccion_estudiante.municipio, "Huajuapan");
    strcpy(e1.direccion_estudiante.entidad,"Oaxaca");
    e1.direccion_estudiante.cp = 67000;
    e1.calificaciones[0] = 10.0;
    e1.asistencias[0] = 1;

    printf("Datos del estudiante:\n");
    printf("Dirección, calle: %s", e1.direccion_estudiante.calle);


    lista_estudiantes[0] = e1;

    return 0;
}
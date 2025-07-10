#include <stdio.h>

struct estudiant_{
    int id;
    int matricula;
    char name[60];
    float calificaciones[4];
    int asistencias[5];
};

typedef struct estudiant_ estudiante;

int main(){
    FILE *cfPtr;

    if((cfPtr = fopen("estudiantes.dat", "rb+")) == NULL){
        puts("No se pudo abrir el archivo...\n");
    } else {
        estudiante estudiante_nuevo = {0, 0, "", {0.0}, {-1}};

        printf("Ingrese id [1 - 100]:");
        scanf("%d", &estudiante_nuevo.id);

        while( estudiante_nuevo.id != 0){
            printf("Ingresar matricula:");
            scanf("%d", &estudiante_nuevo.matricula);
            printf("Ingresar nombre del estudiante:");
            scanf("%s", estudiante_nuevo.name);
            
            fseek(cfPtr, (estudiante_nuevo.id - 1 ) * sizeof(estudiante), SEEK_SET);

            fwrite(&estudiante_nuevo, sizeof(estudiante), 1, cfPtr);

            printf("Ingrese un id [1-100]");
            scanf("%d", &estudiante_nuevo.id);
        }

        fclose(cfPtr);
    }

    return 0;
}
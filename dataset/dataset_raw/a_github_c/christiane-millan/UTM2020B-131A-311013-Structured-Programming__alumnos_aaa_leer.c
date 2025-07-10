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

        printf("%s\t%s\t%s\n", "Id", "Matrícula", "Nombre");
        while(!feof(cfPtr)){
            estudiante estudiante_recuperado = {0, 0, "", {0.0}, {-1}};

            int resultado = fread(&estudiante_recuperado, sizeof(estudiante), 1, cfPtr);

            if(resultado != 0 && estudiante_recuperado.id != 0 && estudiante_recuperado.matricula == 123){
                printf("%d\t%d\t%s", estudiante_recuperado.id, estudiante_recuperado.matricula, 
                estudiante_recuperado.name);
            }
        }

        fclose(cfPtr);
    }

    return 0;
}
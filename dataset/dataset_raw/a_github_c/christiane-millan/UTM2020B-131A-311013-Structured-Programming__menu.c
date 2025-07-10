
void agregar_alumno(){
    printf("Ingresa la matrícula:");
    scanf("%d", &matricula);
    
    printf("Ingresa el inical del nombre del alumno:");
    scanf(" %c", &inicial_nombre);
    printf("Ingresa calificación 1:");
    scanf("%f", &calificacion1);
    printf("Ingresa calificación 2:");
    scanf("%f", &calificacion2);
    printf("Ingresa calificación 3:");
    scanf("%f", &calificacion3);
    printf("Ingresa calificación final:");
    scanf("%f", &calificacionf);
}

void imprimir_menu(){
    printf("Menu de opiones\n");
    printf("1. Agregar alumno\n");
    printf("2. Modificar calificaciones\n");
    printf("3. Imprimir datos del alumno\n");
    printf("4. Salir\n");
    printf("Ingresa una opción: \n");
}

int main () {
    srand(time(0));
    int opcion;
    while (opcion != 4) {
        imprimir_menu();
        scanf("%d", &opcion);
        switch (opcion) {
            case 1: agregar_alumno();
                break;
            case 2: menu_modificacion_calificaciones(&calificacion1, &calificacion2, &calificacion3, &calificacionf);
                break;
            case 3: imprimir_alumno();
                break;
            case 4:
                break;
            default:
                break;
        }

    }
    return 0;
}


float promedio(float c1, float c2, float c3, float cf){
    int potencia = pow(2,3);
    float prom = (((c1 + c2 + c3) / 3) + (cf)) /2;
    return prom;
}

float minimo(float c1, float c2, float c3, float cf){
    float min = c1; 
    if (c1 > c2) { 
        min = c2; 
    }
    if (min > c3){ 
        min = c3; 
    }
    if (min > cf) { 
        min = cf;
    }
    return min;
}

float maximo(float c1, float c2, float c3, float cf){
    float max = c1; 
    if (c1 < c2) { 
        max = c2; 
    }
    if (max < c3){ 
        max = c3; 
    }
    if (max < cf) { 
        max = cf;
    }
    return max;
}

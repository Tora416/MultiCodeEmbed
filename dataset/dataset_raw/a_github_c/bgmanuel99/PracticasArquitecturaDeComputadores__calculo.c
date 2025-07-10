#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void get_media(FILE *fd, char *tipo){
    char cadena[100];
    float suma = 0.1;
    float num[50];

    if(fd == NULL){
        fputs("File error", stderr);
        exit(1);
    }

    char *eptr;
    while(feof(fd) == 0){
        
        strcpy(cadena, fgets(cadena,100 ,fd));
        float result = strtod(cadena, &eptr);
        suma += result;
    }

    fclose(fd);

    printf("%s: La media de los milisegundos es: %f\n",tipo, suma/50);
}


int main(int argc, char** argv)
{
    FILE *fd;
    fd = fopen("miliParalelo.txt", "r");
    get_media(fd, "Paralelo");

    fd = fopen("mili.txt", "r");
    get_media(fd, "Serie");
    
    return 0;
}
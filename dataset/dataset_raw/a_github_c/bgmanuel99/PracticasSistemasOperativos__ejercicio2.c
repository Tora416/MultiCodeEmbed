#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pthread.h>
#define MAXLON 1000


pthread_t thread1, thmain;
pthread_attr_t attr;

void *cuenta (void *);

void *cuenta (void *arg){
    int pos, cont = 0, leidos;
    char cadena[MAXLON];
    int fd;

    fd = open((char) arg, O_RDONLY);
    while ((leidos = read(fd, cadena, MAXLON)) != 0)
    {
        for(pos = 0; pos < leidos; pos++){
            if((cadena[pos] == 'a') || (cadena[pos] == 'A')) cont++;
        }
    }
    printf("Fichero %s: %d caracteres 'a' o 'A' encontrados \n", (char) arg, cont);
    close(fd);
    pthread_exit(NULL);
}

int main(int argc, char *argv[]){
    thmain = pthread_self();
    
    pthread_attr_init(&attr);

    printf("Soy la funcion main y voy a lanzar un thread \n");

    pthread_create(&thread1, &attr, cuenta,"ejemplo.txt");

    sleep(2);
    printf("Fichero ejemplo.txt: 30 caracteres 'a' o 'A' encontrados\n");

    printf("Soy main: he lanzado un thread y termino\n");

    pthread_exit(NULL);

}
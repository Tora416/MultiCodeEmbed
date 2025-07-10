


#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

#define N_PARADAS 5

#define EN_RUTA 0

#define EN_PARADA 1

#define MAX_USUARIOS 40 
#define USUARIOS 4 


int estado= EN_RUTA;
int parada_actual = 0; 
int n_ocupantes= 0; 

int esperando_parada[N_PARADAS]; 

int esperando_bajar[N_PARADAS]; 



pthread_mutex_t esperaSubir[N_PARADAS];
pthread_mutex_t esperaBajar[N_PARADAS];

pthread_t hiloAutobus;

pthread_t usuarios[USUARIOS];

pthread_cond_t suben;
pthread_cond_t bajan;
pthread_cond_t hanSubido;
pthread_cond_t hanBajado;

int min(int num1, int num2){
    if(num1 < num2)
        return num1;
    else
        return num2;
}

void * thread_autobus(void * args) {
    while (1) {
    
        Autobus_En_Parada();
    
        Conducir_Hasta_Siguiente_Parada();
    }
}

void * thread_usuario(int i) {
    int id_usuario, a, b;
    id_usuario = i;

    while (1) {
        a=rand() % N_PARADAS;
        do{
            b=rand() % N_PARADAS;
        } while(a==b);

        printf("Usuario %d se quiere subir en la parada %d y bajar en la %d \n", id_usuario, a, b);
        Usuario(id_usuario,a,b);
    }
}

void Usuario(int id_usuario, int origen, int destino) {

    Subir_Autobus(id_usuario, origen);

    Bajar_Autobus(id_usuario, destino);
}

int main(int argc, char *argv[]) {
    int i;






    for(i=0; i < N_PARADAS; i++){
        pthread_mutex_init(&esperaSubir[i],NULL);
        pthread_mutex_init(&esperaBajar[i],NULL);
    }
    

    pthread_cond_init(&suben, NULL);
    pthread_cond_init(&bajan, NULL);
    pthread_cond_init(&hanSubido, NULL);
    pthread_cond_init(&hanBajado, NULL);
    

    pthread_create(&hiloAutobus, NULL, thread_autobus, NULL);
    

    for (i = 0; i < USUARIOS; i++)
        pthread_create(&usuarios[i], NULL, thread_usuario, (void *) i);



    pthread_join(hiloAutobus, NULL);

    for (i = 0; i < USUARIOS; i++)
        pthread_join(usuarios[i], NULL);

    for(i=0; i<N_PARADAS; i++){
        pthread_mutex_destroy(&esperaSubir[i]);
        pthread_mutex_destroy(&esperaBajar[i]);
    }

    
    pthread_cond_destroy(&suben);
    pthread_cond_destroy(&bajan);
    pthread_cond_destroy(&hanSubido);
    pthread_cond_destroy(&hanBajado);

    return 0;
}

void Autobus_En_Parada(){

    
    
    printf("EL bus está en la parada %d \n", parada_actual);
    estado = EN_PARADA;

    pthread_mutex_lock(&esperaSubir[parada_actual]);
    pthread_mutex_lock(&esperaBajar[parada_actual]);

    
    n_ocupantes -= esperando_bajar[parada_actual];
    
    
    int usuarios_suben = min(MAX_USUARIOS-n_ocupantes, esperando_parada[parada_actual]);
    n_ocupantes += usuarios_suben;
    
    
    pthread_cond_broadcast(&bajan);
    
    
    int j;
    for(j = 0; j < usuarios_suben; j++){
        
        
        
        pthread_cond_broadcast(&suben);
    }
    
    
    while(esperando_parada[parada_actual] > 0 || esperando_bajar[parada_actual] > 0){
        
        
        if(esperando_bajar[parada_actual] > 0 && esperando_parada[parada_actual] == 0)
            
            pthread_cond_wait(&hanBajado, &esperaBajar[parada_actual]);

        
        else if(esperando_bajar[parada_actual] == 0 && esperando_parada[parada_actual] > 0)
            
            pthread_cond_wait(&hanSubido, &esperaSubir[parada_actual]);
        
        
        else{
            
            pthread_mutex_unlock(&esperaSubir[parada_actual]);
            
            pthread_cond_wait(&hanBajado, &esperaBajar[parada_actual]);
            
            pthread_mutex_lock(&esperaSubir[parada_actual]);
        }

        
        
    }
    
    pthread_mutex_unlock(&esperaSubir[parada_actual]);
    pthread_mutex_unlock(&esperaBajar[parada_actual]);

    estado = EN_RUTA;
    printf("El bus está en ruta \n");
}

void Conducir_Hasta_Siguiente_Parada(){

    
    sleep((random() % 5)+1);
    parada_actual = (parada_actual + 1) % N_PARADAS;
}

void Subir_Autobus(int id_usuario, int origen){


    
    pthread_mutex_lock(&esperaSubir[origen]);
    esperando_parada[origen]++;

    
    while(parada_actual != origen || estado != EN_PARADA){
        pthread_cond_wait(&suben, &esperaSubir[origen]);
    }

    
    esperando_parada[origen]--;

    
    if(esperando_parada[origen] == 0)
        pthread_cond_signal(&hanSubido);

    printf("Usuario %d se sube en la parada %d \n", id_usuario, origen);
    
    
    pthread_mutex_unlock(&esperaSubir[origen]);
}

void Bajar_Autobus(int id_usuario, int destino){


    pthread_mutex_lock(&esperaBajar[destino]);
    esperando_bajar[destino]++;

    while(parada_actual != destino || estado != EN_PARADA){
        pthread_cond_wait(&bajan, &esperaBajar[destino]);
    }

    esperando_bajar[destino]--;

    if(esperando_bajar[destino] == 0)
        pthread_cond_signal(&hanBajado);
    
    printf("Usuario %d se baja en la parada %d \n", id_usuario, destino);
    pthread_mutex_unlock(&esperaBajar[destino]);
}
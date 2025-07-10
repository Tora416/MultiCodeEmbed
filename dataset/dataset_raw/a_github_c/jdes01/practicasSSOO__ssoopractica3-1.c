#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

void * compra();
void * suministro();

int camisetas[5] = {1,2,3,4,5};

pthread_mutex_t mutex_acceso = PTHREAD_MUTEX_INITIALIZER;

int main(int argc, char * argv[]){

    srand(time(NULL)); 

    int n; 

    printf("introduce el numero de clientes:\n");
    scanf("%i", &n);

    pthread_t clientes[n];

    int m; 
    m = 5;

    pthread_t proveedores[m];

    for (int i = 0; i < n; i++){ pthread_create(&clientes[i], NULL, compra, NULL); } 
                                                                                     
                                                                                     
    for (int i = 0; i < m; i++){ pthread_create(&proveedores[i], NULL, suministro, NULL); } 
                                                                                            

    for (int i = 0; i < n; i++){ pthread_join(clientes[i], NULL); } 
                                                                                    

    for (int i = 0; i < m; i++) { pthread_join(proveedores[i], NULL); } 
                                                                                    

    printf("stock: %i %i %i %i %i \n",camisetas[0], camisetas[1], camisetas[2], camisetas[3], camisetas[4]);
}

void * compra(){

    int modelo=(rand()%4)+1; 

    int cantidad=(rand()%10)+1; 

    printf("stock: %i %i %i %i %i \n",camisetas[0], camisetas[1], camisetas[2], camisetas[3], camisetas[4]);

    printf("se va a comprar el modelo %i %i veces \n",modelo,cantidad);

    pthread_mutex_lock(&mutex_acceso);

        camisetas[modelo-1] = camisetas[modelo-1] - cantidad;

    pthread_mutex_unlock(&mutex_acceso);

    printf("stock: %i %i %i %i %i \n",camisetas[0], camisetas[1], camisetas[2], camisetas[3], camisetas[4]);

    pthread_exit(NULL); 

}

void * suministro(){

    int modelo=(rand()%4)+1; 

    int cantidad=(rand()%10)+1; 

    printf("stock: %i %i %i %i %i \n",camisetas[0], camisetas[1], camisetas[2], camisetas[3], camisetas[4]);

    printf("se va a suministrar el modelo %i %i veces \n",modelo,cantidad);

    pthread_mutex_lock(&mutex_acceso);

        camisetas[modelo-1] = camisetas[modelo-1] + cantidad;

    pthread_mutex_unlock(&mutex_acceso);

    printf("stock: %i %i %i %i %i \n",camisetas[0], camisetas[1], camisetas[2], camisetas[3], camisetas[4]);

    pthread_exit(NULL); 

}
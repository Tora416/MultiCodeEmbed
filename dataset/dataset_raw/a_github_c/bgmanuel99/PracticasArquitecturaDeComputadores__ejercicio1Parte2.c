#include <math.h>
#include <mpi.h> 
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int main(int argc, char *argv[]) {
    int rank, 
    size, 
    valor; 
    MPI_Status status; 

    MPI_Init(&argc, &argv); 
    
    MPI_Comm_size(MPI_COMM_WORLD, &size); 
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); 
    
    srand(time(NULL));

    if (rank == 0) {
        valor = rand() % 4 + 1;
        valor *= valor;
    }

    printf("[%d]: Antes del Bcast, el valor es %d \n", rank, valor);

    MPI_Bcast(&valor, 1, MPI_INT, 0, MPI_COMM_WORLD);
    
    printf("[%d]: Despues del Bcast, el valor es %d \n", rank, valor);

    MPI_Finalize();

    return 0;
} 
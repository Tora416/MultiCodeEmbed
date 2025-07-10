#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv){
    int size, rank, value;
    MPI_Status status;

    MPI_Init(&argc,&argv);

    MPI_Comm_size (MPI_COMM_WORLD, &size);
    MPI_Comm_rank (MPI_COMM_WORLD, &rank);

    if(rank == 0){
        printf("Introduce el valor que quieres que se comunique: ");
        scanf("%d", &value);
        printf("[%d]: envio el dato: %d a [%d]\n", rank, value, rank+1);
        MPI_Send(&value, 1, MPI_INT, rank+1, size, MPI_COMM_WORLD);
    }else{
        MPI_Recv(&value, 1, MPI_INT, rank-1, size, MPI_COMM_WORLD, &status);
        if(rank < size-1) {
            printf("[%d]: recibo el dato: %d de [%d] y lo envio a [%d]\n", rank, value, rank-1, rank+1);
            MPI_Send(&value, 1, MPI_INT, rank+1, size, MPI_COMM_WORLD);
        }else{
            printf("[%d]: recibo el dato: %d de [%d] y termino\n", rank, value, rank-1);
        }
    }

    MPI_Finalize();
    
    return 0;
}
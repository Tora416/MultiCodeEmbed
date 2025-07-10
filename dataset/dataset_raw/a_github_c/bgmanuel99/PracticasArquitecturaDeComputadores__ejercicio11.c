#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
 
int matriz[4][4] = {
    {1,2,3,4},
    {5,6,7,8},
    {9,10,11,12},
    {13,14,15,16}
};

int main(int argc, char* argv[]){
    int size, rank, buffer[16];

    MPI_Init(&argc, &argv);
    
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int my_row[4];
    
    for(int i = 0; i < 4; i++ ){
        my_row[i] = matriz[i][rank];
    }
 
    MPI_Allgather(&my_row, 4, MPI_INT, buffer, 4, MPI_INT, MPI_COMM_WORLD);
    MPI_Allgather(&my_row, 4, MPI_INT, buffer, 4, MPI_INT, MPI_COMM_WORLD);
    MPI_Allgather(&my_row, 4, MPI_INT, buffer, 4, MPI_INT, MPI_COMM_WORLD);
    MPI_Allgather(&my_row, 4, MPI_INT, buffer, 4, MPI_INT, MPI_COMM_WORLD);

    if(rank==0){
        for(int j = 0; j < 16; j++){
            printf("%d ", buffer[j]);
            if(j == 3 || j == 7 || j == 11) printf("\n");
        }
        printf("\n");
    }

    MPI_Finalize();
 
    return 0;
}
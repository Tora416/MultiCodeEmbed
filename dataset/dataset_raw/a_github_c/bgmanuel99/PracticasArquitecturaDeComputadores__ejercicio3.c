#include <stdio.h>
#include <string.h>
#include "mpi.h"

int main(int argc, char **argv){
  MPI_Init(NULL, NULL);
 double A[10000];
 double B[10000];
 int world_rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
  int world_size;
  MPI_Comm_size(MPI_COMM_WORLD, &world_size);


  if (world_rank != 0) {

    int i = 0;

    for(i; i < 10000; i++){
        A[i]=world_rank;
    }
    MPI_Recv(&B, 10000, MPI_INT, world_rank - 1, 0, MPI_COMM_WORLD,
             MPI_STATUS_IGNORE);
    printf("Process %d received B[109] = %d from process %d\n", world_rank, B[109],
           world_rank - 1);
  } else {
    int i = 0;
    for(i; i < 10000; i++){
        A[i]=world_rank;
    }
  }
    printf("%d =>rank to : %d\n",world_rank,(world_rank + 1) % world_size);
  MPI_Send(&A, 10000, MPI_INT, (world_rank + 1) % world_size, 0,
           MPI_COMM_WORLD);

  if (world_rank == 0) {
    MPI_Recv(&B, 10000, MPI_INT, world_size - 1, 0, MPI_COMM_WORLD,
             MPI_STATUS_IGNORE);
    printf("Process %d received B[109] = %d \n", world_rank, 3);
  }
  MPI_Finalize();



}
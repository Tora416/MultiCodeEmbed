#include <mpi.h>
#include <stdio.h>
#include <time.h>

int main(int argc, char** argv)
{
    clock_t t_ini, t_fin;
    double secs;

    int nproc=50;
    int myrank;

    t_ini = clock();

    MPI_Init(&argc,&argv);
    
    MPI_Comm_size (MPI_COMM_WORLD, &nproc);
    MPI_Comm_rank (MPI_COMM_WORLD,&myrank);

    printf("Hola mundo, soy el proceso %d de un total de %d \n",myrank,nproc);

    MPI_Finalize();

    t_fin = clock();

    secs = (double)(t_fin - t_ini)/ CLOCKS_PER_SEC;
    printf("%.16g milisegundos\n", secs * 1000.0);
    
    return 0;
}

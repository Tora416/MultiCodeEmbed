#include<stdio.h>
#include<mpi.h>
#include<stdlib.h>
int main(int argc, char* argv[])
{
    int rank, size;
    int k;
    int buff_size=MPI_BSEND_OVERHEAD+sizeof(int);
    char* buff=(char*)malloc(buff_size*sizeof(int));
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    int arr[7];
    if(size!=8)
    {
        printf("\nUse 8 processes\n");
        MPI_Abort(MPI_COMM_WORLD,EXIT_FAILURE);
    }
    if(rank==0)
    {
        MPI_Buffer_attach(buff,buff_size);
        printf("Please enter 7 integers.\n");
        for(int i=0;i<7;i++)
        {
            scanf("%d",&arr[i]);
        }
        printf("Process[%d] sending the elements.\n",rank);
        for(int i=1;i<8;i++)
        {
            MPI_Bsend(&arr[i-1],1,MPI_INT,i,0,MPI_COMM_WORLD);
        }
    }
    else
    {
        MPI_Recv(&k,1,MPI_INT,0,0,MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        if(rank%2==0)
        {
            printf("Process[%d] recieved: %d and the square is: %d \n",rank, k,k*k);
        }
        else
        {
            printf("Process[%d] recieved: %d and the cube is: %d \n",rank, k,k*k*k);
        }
    }
    MPI_Buffer_detach(buff, &buff_size);
    MPI_Finalize();
}
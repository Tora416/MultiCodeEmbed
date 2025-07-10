#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>t
#include<string.h>

int main(int argc,char* argv[]){
    int rank,size,num;
    char st[10];
    char res[10];
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    if(size!=4){
        printf("\nUse 4 processes\n");
        MPI_Abort(MPI_COMM_WORLD,EXIT_FAILURE);
    }
    if(rank==0){
        printf("\nProcess[%d]: Sending numbers\n",rank);
        num=1;
        MPI_Send(&num,1,MPI_INT,1,0,MPI_COMM_WORLD);
        num=2;
        MPI_Send(&num,1,MPI_INT,2,0,MPI_COMM_WORLD);
        num=3;
        MPI_Send(&num,1,MPI_INT,3,0,MPI_COMM_WORLD);
        
    }else{
        MPI_Recv(&num,1,MPI_INT,0,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
        printf("\nProcess[%d]: Received %d\n",rank,num);
    }
    MPI_Finalize();
    return 0;
}
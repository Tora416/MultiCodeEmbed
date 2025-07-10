#include <stdio.h>
#include <string.h>
#include "mpi.h"
int main(int argc, char **argv){

 int rank, count;
 char msg[20];
 MPI_Status status;   
 MPI_Init( &argc , &argv);
 MPI_Comm_rank( MPI_COMM_WORLD ,&rank);
 int i= 0;
 while(i<10){
     if(rank==0){
     strcpy(msg,"Hello World");
     MPI_Send( msg , 13 , MPI_CHAR , 1 , 100 , MPI_COMM_WORLD);

    MPI_Recv( msg , 13 , MPI_CHAR , 1 , 100 , MPI_COMM_WORLD , &status);
            printf("Master: El mensaje es: %s\n",msg);


     
    }else
    {
        MPI_Recv( msg , 13 , MPI_CHAR , 0 , 100 , MPI_COMM_WORLD , &status);
        printf("Secundario: El mensaje es: %s\n",msg);
        strcpy(msg,"Bye World");
        MPI_Send( msg , 13 , MPI_CHAR , 0 , 100 , MPI_COMM_WORLD);
    }
    i++;
 }
    

    MPI_Finalize();


}
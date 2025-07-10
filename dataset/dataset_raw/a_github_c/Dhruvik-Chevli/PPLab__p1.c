#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>
#include<string.h>

int main(int argc,char* argv[]){
    int rank,size;
    char st[10];
    char res[10];
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    if(size!=2){
        printf("\nUse 2 processes\n");
        MPI_Abort(MPI_COMM_WORLD,EXIT_FAILURE);
    }
    if(rank==0){
        printf("Enter string to toggle\n");
        gets(st);
        printf("\nProcess[%d]: Sending string %s\n",rank,st);
        MPI_Ssend(st,9,MPI_CHAR,1,0,MPI_COMM_WORLD);
        MPI_Recv(res,9,MPI_CHAR,1,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
        printf("\nProcess[%d]: Received string %s\n",rank,res);
    }else{
        MPI_Recv(st,9,MPI_CHAR,0,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
        printf("\nProcess[%d]: Received string %s\n",rank,st);
    for(int i=0;i<strlen(st);i++){
        if(st[i]>='a'&&st[i]<='z') st[i]-=32;
        else if(st[i]>='A'&&st[i]<='Z') st[i]+=32;
    }
    printf("\nProcess[%d]: Sending string %s\n",rank,st);
        MPI_Ssend(st,9,MPI_CHAR,0,0,MPI_COMM_WORLD);
    }
    MPI_Finalize();
    return 0;
}
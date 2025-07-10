#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>

long fact(int a){
    if(a==0) return 1;
    return a*fact(a-1);
}

int main(int argc,char* argv[]){
    int rank,size,*a=NULL,c;
    long res,*b=NULL;
    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    a=(int*)malloc(size*sizeof(int));
    b=(long*)malloc(size*sizeof(long));
    if(rank==0){
        printf("Enter %d numbers.\n",size);
        for(int i=0;i<size;i++)
            scanf("%d",&a[i]);
    }
    MPI_Scatter(a,1,MPI_INT,&c,1,MPI_INT,0,MPI_COMM_WORLD);
    res=fact(c);
    printf("Process[%d]: Factorial of %d is %ld\n",rank,c,res);
    MPI_Gather(&res,1,MPI_LONG,b,1,MPI_LONG,0,MPI_COMM_WORLD);
    if(rank==0){
        res=0;
        for(int i=0;i<size;i++) res+=b[i];
        printf("Process[%d]: The sum of all factorials is %ld\n",rank,res);
    }
    MPI_Finalize();
    return 0;
}


#include<stdio.h>
#define SIZE 10


void CopyArray(int *ptrA , int *ptrB){
    int i;

    for(i=0 ; i<SIZE ; i++){
        *ptrB = *ptrA;
        ptrA++;
        ptrB++;
    }
}

int main(void){
    setvbuf(stdout , NULL , _IONBF , 0);
    setvbuf(stdout , NULL , _IONBF , 0);

    int i;
    int array_A[SIZE];
    int array_B[SIZE];
    int *ptrA = array_A;
    int *ptrB = array_B;
    
    printf("Enter elements of array A: ");
    for(i=0 ; i<SIZE ; i++){
        scanf("%d",ptrA);
        ptrA++;
    }

    
    CopyArray(array_A,array_B);

    
    for(i=0 ; i<SIZE ; i++){
        printf("ArrayB[%d] = %d \n",i,*ptrB);
        ptrB++;
    }

    return 0;
}

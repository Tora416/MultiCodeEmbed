

#include<stdio.h>
#define SIZE 10


void Swap(int *ptrA , int *ptrB){
    int temp;
    int i;

    for(i=0 ; i<SIZE ; i++){
        temp = *ptrA;
        *ptrA = *ptrB;
        *ptrB = temp;
        ptrA++;
        ptrB++;
    }
}

int main(void){
    setvbuf(stdout , NULL , _IONBF , 0);
    setvbuf(stderr , NULL , _IONBF , 0);

    int arrayA[SIZE];
    int arrayB[SIZE];

    int *ptrA = arrayA;
    int *ptrB = arrayB;

    int i;

    
    printf("Enter elements of first array: ");
    for(i=0 ; i<SIZE ; i++){
        scanf("%d",ptrA);
        ptrA++;
    }

    printf("Enter elements of second array: ");
    for(i=0 ; i<SIZE ; i++){
        scanf("%d",ptrB);
        ptrB++;
    }

    
    ptrA = arrayA;
    ptrB = arrayB;


    printf("\n");
    
    printf("Array elements before swapping\n");
    printf("Elements of first array:\n");
    for(i=0 ; i<SIZE ; i++){
        printf("ArrayA[%d] = %d\n",i,*ptrA);
        ptrA++;
    }

    printf("\n");
    printf("Elements of second array:\n");
    for(i=0 ; i<SIZE ; i++){
        printf("ArrayB[%d] = %d\n",i,*ptrB);
        ptrB++;
    }

    
    Swap(arrayA,arrayB);

    
    ptrA = arrayA;
    ptrB = arrayB;

    printf("\n");
    
    printf("Array elements after swapping\n");
    printf("Elements of first array:\n");
    for(i=0 ; i<SIZE ; i++){
        printf("ArrayA[%d] = %d\n",i,*ptrA);
        ptrA++;
    }

    printf("\n");
    printf("Elements of second array:\n");
    for(i=0 ; i<SIZE ; i++){
        printf("ArrayB[%d] = %d\n",i,*ptrB);
        ptrB++;
    }

    return 0;
}

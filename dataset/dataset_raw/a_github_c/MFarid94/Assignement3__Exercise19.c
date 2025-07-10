

#include<stdio.h>
#define TRUE 1
#define FALSE 0


int CheckIdentical(int array_A[], int array_B[] ,int size){
    int i;

    
    for(i=0 ; i<size ; i++){
        if(array_A[i] != array_B[i]){
            return 1;
        }
    }

    
    return 0;
}

int main(void){
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);

    int size = 5;
    int arrayA[size];
    int arrayB[size];
    int i;
    int result;

    printf("Enter array A elements: ");
    
    for(i=0 ; i<size ; i++){
        scanf("%d",&arrayA[i]);
    }


    printf("Enter array B elements: ");
    
    for(i=0 ; i<size ; i++){
        scanf("%d",&arrayB[i]);
    }

    
    result = CheckIdentical(arrayA, arrayB ,size);

    if(result == TRUE){
        printf("Two arrays are not identical");
    }
    else if(result == FALSE){
        printf("Two arrays are identical");
    }

    return 0;
}

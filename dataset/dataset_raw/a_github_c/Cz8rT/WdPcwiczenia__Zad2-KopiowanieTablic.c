#include <stdio.h>

void copyArrayNormal(int sourceArray[], int outputArray[], int size);
void copyArrayPointer(int sourceArray[], int outputArray[], int size);

int main()
{
   int array1[7] = {8, 32, -4, 5, 6, 93, 345};
   int array2[7];
   int array3[7];
   int arraySize = sizeof(array1)/sizeof(*array1);

    copyArrayNormal(array1, array2, arraySize);
    copyArrayPointer(array1, array3, arraySize);

    printf("array1: ");
    for(int i = 0; i < arraySize; i++){
        printf("%d ", array1[i]);
    }
    printf("\n");

    printf("array2: ");
    for(int i = 0; i < sizeof(array2)/sizeof(*array2); i++){
        printf("%d ", array2[i]);
    }
    printf("\n");

    printf("array3: ");
    for(int i = 0; i < sizeof(array3)/sizeof(*array3); i++){
        printf("%d ", array3[i]);
    }
    printf("\n");

    return 0;
}

void copyArrayNormal(int sourceArray[], int outputArray[], int size){
    for(int i = 0; i < size; i++){
        outputArray[i] = sourceArray[i];
    }
};

void copyArrayPointer(int sourceArray[], int outputArray[], int size){
    int * pointerSource = sourceArray;
    int * pointerOutput = outputArray;
    for(int i = 0; i < size; i++){
        *pointerOutput = *pointerSource;
        pointerSource++;
        pointerOutput++;
    }
};

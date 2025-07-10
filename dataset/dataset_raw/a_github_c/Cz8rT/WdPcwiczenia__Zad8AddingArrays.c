#include <stdio.h>

void AddArraysPointer(int sourceArray[], int outputArray[], int size);

int main()
{
   int array1[8] = { 8, 32, -4, 43, 200, 4000, -6432, 7};

   int array2[8] = { 2, -32, -4, 653, -199, 4010, -6432, 14};
   int array3[8];

   int arraySize = sizeof(array1)/sizeof(*array1);

    addArraysPointer(array1, array2, array3, arraySize);

    printf("array1: ");
    for(int i = 0; i < arraySize; i++){
            printf("%d ", array1[i]);
    }

    printf("\n\narray2: ");
    for(int i = 0; i < arraySize; i++){
            printf("%d ", array2[i]);
    }

    printf("\n\narray3: ");
    for(int i = 0; i < arraySize; i++){
            printf("%d ", array3[i]);
    }

    printf("\n");
    return 0;
}

void addArraysPointer(int sourceArray1[], int sourceArray2[], int outputArray[], int size){
    int * pointerSource1 = sourceArray1;
    int * pointerSource2 = sourceArray2;
    int * pointerOutput = outputArray;
    for(int i = 0; i < size; i++){
        *pointerOutput = *pointerSource1 + *pointerSource2;
        pointerSource1++;
        pointerSource2++;
        pointerOutput++;
    }
};

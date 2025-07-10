#include <stdio.h>

void copyArrayNormal(int sourceArray[], int outputArray[], int size);
void copyArrayPointer(int sourceArray[], int outputArray[], int size);

int main()
{
   int array1[7] = { 8, 32, -4, 43, 200, 4000, -6432};

   int array2[3];
   int array3[3];

   int arraySize1 = sizeof(array1)/sizeof(*array1);
   int arraySize2 = sizeof(array2)/sizeof(*array2);
    int arraySize3 = sizeof(array3)/sizeof(*array3);

    copyArrayNormal(&array1[2], array2, arraySize2); 
    copyArrayPointer(&array1[2], array3, arraySize3);

    printf("array1: ");
    for(int i = 0; i < arraySize1; i++){
            printf("%d ", array1[i]);
    }

    printf("\n\narray2: ");
    for(int i = 0; i < arraySize2; i++){
            printf("%d ", array2[i]);
    }

    printf("\n\narray3: ");
    for(int i = 0; i < arraySize3; i++){
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

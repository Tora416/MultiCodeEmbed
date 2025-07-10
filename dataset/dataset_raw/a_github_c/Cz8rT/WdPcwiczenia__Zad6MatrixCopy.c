#include <stdio.h>

void copyArrayNormal(int sourceArray[], int outputArray[], int size);
void copyArrayPointer(int sourceArray[], int outputArray[], int size);

int main()
{
   int array1[7][3] = {
        {8, 32, -4},
        {5, 6, 93},
        {345, 32, -32},
        {3, 3, -3},
        {-6, -5, -5},
        {0, 0, 0},
        {0, 2, -2}
        };

   int array2[7][3];
   int array3[7][3];
   int arraySizeOut = sizeof(array1)/sizeof(*array1);
   int arraySizeIn = sizeof(array1[0])/sizeof(*array1[0]);

    for(int i = 0; i < arraySizeOut; i++){
        copyArrayNormal(array1[i], array2[i], arraySizeIn);
    }
    for(int i = 0; i < arraySizeOut; i++){
        copyArrayPointer(array1[i], array3[i], arraySizeIn);
    }

    printf("array1");
    for(int i = 0; i < arraySizeOut; i++){
        printf("\nPodtablica: ");
        for(int j = 0; j < arraySizeIn; j++){
            printf("%d ", array1[i][j]);
        }
    }

    printf("\n\narray2");
    for(int i = 0; i < arraySizeOut; i++){
        printf("\nPodtablica: ");
        for(int j = 0; j < arraySizeIn; j++){
            printf("%d ", array2[i][j]);
        }
    }


    printf("\n\narray3");
    for(int i = 0; i < arraySizeOut; i++){
        printf("\nPodtablica: ");
        for(int j = 0; j < arraySizeIn; j++){
            printf("%d ", array3[i][j]);
        }
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

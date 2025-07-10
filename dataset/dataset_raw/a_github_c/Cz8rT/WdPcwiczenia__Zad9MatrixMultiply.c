#include <stdio.h>

void showArray(int sourceArray[], int size);
void multiplyByTwo(int sourceArray[], int size);

int main()
{
   int array[3][5] = {
            {8, 32, -4, 43, 200},
            {-8, 102, -8, -3, 100},
            {18, -2, -1, 21, 400},
       };

   int arraySize = sizeof(array)/sizeof(*array);

    showArray(array, arraySize);
    multiplyByTwo(array, arraySize);
    printf("\n");
    showArray(array, arraySize);

    printf("\n");
    return 0;
}

void showArray(int sourceArray[], int size){
    int * pointerSourceArray = sourceArray;
    printf("array\n");
    for(int i = 0; i < size; i++){
        printf("Podtablica: ");
        for(int j = 0; j < 5; j++){
            printf("%d ", pointerSourceArray[j+(i*5)]);
        }
        printf("\n");
    }
}

void multiplyByTwo(int sourceArray[], int size){
    int * pointerSourceArray = sourceArray;
    for(int i = 0; i < size*5; i++){
        *pointerSourceArray = *pointerSourceArray * 2;
        pointerSourceArray++;
    }
};

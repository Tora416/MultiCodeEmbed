#include <stdio.h>

float difference(float sourceArray[]);

int main()
{
   float array[10] = {8.2, 32, -4.56, 5.666, 6.32, 93, 345, -74.32, 424.23, -425.53, 89, 56};

    printf("Roznica najwiekszej i najmniejszej wartosci, to: %.2f\n", difference(array));

    return 0;
}

float difference(float sourceArray[]){
    int size = 12;
    float biggest;
    float smallest;
    float diff;
    for(int i = 0; i < size; i++){
        if(biggest < sourceArray[i]){
            biggest = sourceArray[i];
        }
        if(smallest > sourceArray[i]){
            smallest = sourceArray[i];
        }
    }

    diff = biggest - smallest;
    return diff;
};

#include <stdio.h>
#include <stdlib.h>

void connectArrays(unsigned int, int * array1, int * array2, double * array3);

int main()
{
    int one[8] = {5, 6, 8, 8, 10, -2, 0, 121};
    int two[8] = {2, 1, 3, -4, 10, 21, 2, 233};
    double three[16];
    unsigned int naturalNumber = 8;

    printf("Elementy tablicy1: ");
    for(int i = 0; i < (sizeof(one)/sizeof(one[0])); i++){
        printf("%d ", one[i]);
    }
    printf("\nElementy tablicy2: ");
    for(int i = 0; i < (sizeof(two)/sizeof(two[0])); i++){
        printf("%d ", two[i]);
    }

    connectArrays(naturalNumber, one, two, three);

    printf("\nElementy tablicy3: ");
    for(int i = 0; i < (sizeof(three)/sizeof(three[0])); i++){
        printf("%.f ", three[i]);
    }

    getchar();;
    return 0;
}

void connectArrays(unsigned int n, int * array1, int * array2, double * array3){
    int counterEven = 0;
    int counterOdd = 0;
    int i = 0;
    for(i; i < 2*n; i++){
        if(i % 2 == 0){
            array3[i] = array2[counterEven];
            counterEven++;
        } else {
            array3[i] = array1[counterOdd];
            counterOdd++;
        }
    }
};

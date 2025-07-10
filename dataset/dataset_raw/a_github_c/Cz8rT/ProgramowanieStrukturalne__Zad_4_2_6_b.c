#include <stdio.h>
#include <stdlib.h>

void copyArrays(unsigned int, int * array1, int * array2);

int main()
{
    int one[5] = {5, 6, 8, 8, 10};
    int two[5];

    printf("Elementy tablicy1: ");
    for(int i = 0; i < (sizeof(one)/sizeof(one[0])); i++){
        printf("%d ", one[i]);
    }

    copyArrays(5, one, two);

    printf("\nElementy tablicy2: ");
    for(int i = 0; i < (sizeof(two)/sizeof(two[0])); i++){
        printf("%d ", two[i]);
    }

    getchar();;
    return 0;
}

void copyArrays(unsigned int n, int * array1, int * array2){
    int i = 0;
    for(i; i < n; i++){
        array2[i] = array1[n-1-i];
    }
};

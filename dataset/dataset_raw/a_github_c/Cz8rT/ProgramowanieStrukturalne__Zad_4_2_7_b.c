#include <stdio.h>
#include <stdlib.h>

void biggerElement(unsigned int, int * array1, int * array2, int * array3);

int main()
{
    int one[8] = {5, 6, 8, 8, 10, -2, 0, 121};
    int two[8] = {2, 1, 3, -4, 10, 21, 2, 233};
    int three[8];
    unsigned int naturalNumber = 8;

    printf("Elementy tablicy1: ");
    for(int i = 0; i < (sizeof(one)/sizeof(one[0])); i++){
        printf("%d ", one[i]);
    }
    printf("\nElementy tablicy2: ");
    for(int i = 0; i < (sizeof(two)/sizeof(two[0])); i++){
        printf("%d ", two[i]);
    }

    biggerElement(naturalNumber, one, two, three);

    printf("\nElementy tablicy3: ");
    for(int i = 0; i < (sizeof(three)/sizeof(three[0])); i++){
        printf("%d ", three[i]);
    }

    getchar();;
    return 0;
}

void biggerElement(unsigned int n, int * array1, int * array2, int * array3){
    int i = 0;
    for(i; i < n; i++){
        if(array1[i] > array2[i]){
            array3[i] = array1[i];
        } else {
            array3[i] = array2[i];
        }
    }
};

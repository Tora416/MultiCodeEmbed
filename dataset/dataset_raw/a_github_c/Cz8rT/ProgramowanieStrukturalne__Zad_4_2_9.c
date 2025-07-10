#include <stdio.h>
#include <stdlib.h>

void changeCells(unsigned int, int * array1, int * array2, int * array3);

int main()
{
    int one[8] = {55, 6, -8, -8, 10, 22, 0, 121};
    int two[8] = {22, 1, -3, -4, 10, 21, 2, 233};
    int three[8] = {33, 4, -9, -9, 99, 99, 0, 400};
    unsigned int naturalNumber = 8;

    printf("Elementy tablicy1: ");
    for(int i = 0; i < (sizeof(one)/sizeof(one[0])); i++){
        printf("%d ", one[i]);
    }
    printf("\nElementy tablicy2: ");
    for(int i = 0; i < (sizeof(two)/sizeof(two[0])); i++){
        printf("%d ", two[i]);
    }
    printf("\nElementy tablicy3: ");
    for(int i = 0; i < (sizeof(three)/sizeof(three[0])); i++){
        printf("%d ", three[i]);
    }

    printf("\n\nMieszanie tablic!!!\n\n");
    changeCells(naturalNumber, one, two, three);

     printf("Elementy tablicy1: ");
    for(int i = 0; i < (sizeof(one)/sizeof(one[0])); i++){
        printf("%d ", one[i]);
    }
    printf("\nElementy tablicy2: ");
    for(int i = 0; i < (sizeof(two)/sizeof(two[0])); i++){
        printf("%d ", two[i]);
    }
    printf("\nElementy tablicy3: ");
    for(int i = 0; i < (sizeof(three)/sizeof(three[0])); i++){
        printf("%d ", three[i]);
    }

    getchar();;
    return 0;
}

void changeCells(unsigned int n, int * array1, int * array2, int * array3){
    int i = 0;
    for(i; i < n; i++){
        int a = array1[i], b = array2[i], c = array3[i];
        int max = (a>=b && a>=c) ? a : (b>=a&&b>=c) ? b : c;
        int min = (a<=b && a<=c) ? a : (b<=a&&b<=c) ? b : c;
        int mid = (c!=max && c!=min) ? c : (b!=max && b!=min) ? b : a;
        array1[i] = max;
        array2[i] = mid;
        array3[i] = min;
    }
};

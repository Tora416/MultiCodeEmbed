#include <stdio.h>
#include <stdbool.h>
#define true 1
#define false 0

int main(){
    float f;
    double d;
    long double ld;
    int i;
    long l;
    long long ll;
    char c = 97;
    short s;

    int array[10] = {1, 2, 3, 4, 5, 6, 7, 10};
    int *p_array = array;

    printf("Tamaño de c es: %lu, el tamaño de char es:  %lu\n", sizeof c, sizeof(char));
    printf("Tamaño de i es: %lu, el tamaño de int es:  %lu\n", sizeof i, sizeof(int));
    printf("Tamaño de s es: %lu, el tamaño de short es:  %lu\n", sizeof s, sizeof(short));
    printf("Tamaño de l es: %lu, el tamaño de long es:  %lu\n", sizeof l, sizeof(long));
    printf("Tamaño de ll es: %lu, el tamaño de long long es:  %lu\n", sizeof l, sizeof(long long));
    printf("Tamaño de f es: %lu, el tamaño de float es:  %lu\n", sizeof f, sizeof(float));
    printf("Tamaño de d es: %lu, el tamaño de double es:  %lu\n", sizeof d, sizeof(double));
    printf("Tamaño de ld es: %lu, el tamaño de long double es:  %lu\n", sizeof ld, sizeof(long double));
    
    printf("Tamaño del arreglo es %lu\n", sizeof array);
    printf("Tamaño del size_t es %lu\n", sizeof(size_t));
    printf("Tamaño del apuntador al arreglo es %lu\n", sizeof p_array);
    printf("*p_array %d\n", *p_array);
    printf("p_array %p\n", p_array);


    return false;
}
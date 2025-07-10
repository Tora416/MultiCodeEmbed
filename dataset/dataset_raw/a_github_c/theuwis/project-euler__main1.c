#include <stdio.h>
#include <stdlib.h>
#include <math.h> 



int main(void){
    long input = 600851475143;
    int i;


    
    while(input%2 == 0){
        printf("%d ", 2);
        input = input/2;
    }

    
    for(i = 3; i <= sqrt(input); i += 2){
        while(input%i == 0){
            printf("%d ", i);
            input = input/i;
        }
    }

    
    if (input > 2) printf ("%ld ", input);
    printf("\n");
    
    return EXIT_SUCCESS;
}
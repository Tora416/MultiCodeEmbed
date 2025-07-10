#include <stdio.h>
#include <stdlib.h>


int main(void){
    int i = 1, j, sum = 0, nr_of_divisors = 0;

    while(1){
        
        for(j = 1; j <= i; j++){
            sum += j;
        }

        
        for(j = 1; j <= sum; j++){
            if(sum % j == 0) nr_of_divisors++;
        }

        
        if(nr_of_divisors > 500){
            printf("answer=%d (nr=%d, nr_div=%d)\n", sum, i, nr_of_divisors);
            break;
        }

        printf("(%10d) %d\n", i, nr_of_divisors);

        i++;
        sum = 0;
        nr_of_divisors = 0;
    }

    return EXIT_SUCCESS;
}
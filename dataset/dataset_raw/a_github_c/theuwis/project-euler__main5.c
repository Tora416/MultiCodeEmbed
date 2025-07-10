#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define NR_PRIME 10001


int main(void){
    long answer = 1;
    int nr_of_primes_found = 0, i;
    bool is_prime = true;

    while(1){

        
        for(i = 2; i <= answer/2; i++){
            if(answer % i == 0){
                is_prime = false;
                break;
            }
        }

        
        if(is_prime){
            nr_of_primes_found++;

            
            if(nr_of_primes_found == NR_PRIME - 1){
                break;
            }           
        }

        is_prime = true;
        answer++;
    }


    printf("answer=%ld\n", answer);
    return EXIT_SUCCESS;
}
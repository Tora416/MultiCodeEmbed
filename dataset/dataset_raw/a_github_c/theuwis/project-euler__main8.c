#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


int main(void){
    int i, j;
    long answer = 0;
    bool is_prime = true;


    for(i = 2; i < 2000000; i++){
        
        for(j = 2; j <= i/2; j++){
            if(i % j == 0){
                is_prime = false;
                break;
            }
        }

        if(is_prime){
            answer += i;
        }

        is_prime = true;
    }

    printf("answer=%ld\n", answer);
    return EXIT_SUCCESS;
}

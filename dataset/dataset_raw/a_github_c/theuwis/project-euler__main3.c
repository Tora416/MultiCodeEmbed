#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main(void){
    long answer = 1;
    int div_nr;
    bool div_by_nr = true;

    while(1){
        
        for(div_nr = 1; div_nr <= 20; div_nr++){
            if(answer % div_nr != 0){
                div_by_nr = false;
                break;
            }
        }

        
        if(div_by_nr){
            break;
        }

        div_by_nr = true;
        answer++;
    }

    printf("answer=%ld\n", answer);
    return EXIT_SUCCESS;
}
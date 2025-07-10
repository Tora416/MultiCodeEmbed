#include <stdio.h>
#include <stdlib.h>

#define STEP_SIZE 301
#define TOTAL_LEN 2018
int array[TOTAL_LEN];

int main(void){
    int curr_nr = 0, curr_pos = 0;

    while(curr_nr < TOTAL_LEN - 1){
        for(int i = 0; i < STEP_SIZE; i++){
            if(curr_pos < curr_nr){
                curr_pos++;
            }
            else{
                curr_pos = 0;
            }
        }
        curr_pos++;

        
        for(int i = curr_nr; i > curr_pos; i--){
            array[i] = array[i - 1];
        }

        curr_nr++;
        array[curr_pos] = curr_nr;
    }

    printf("answer=%d\n", array[curr_pos + 1]);
    return EXIT_SUCCESS;
}

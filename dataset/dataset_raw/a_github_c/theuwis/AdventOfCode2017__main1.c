#include <stdio.h>
#include <stdlib.h>

int input = 347991;

void check_end(int * i, int * col, int * row){
    if(*i == input){
        printf("answer=%d (%d, %d)\n", (abs(*col) + abs(*row)), *col, *row);
        exit(EXIT_SUCCESS);
    }
}

int main(void){
    int current_ring_multiplier = 1;
    int col = 1, row = 0;
    int i = 2;

    while(1){
        
        for(int j = 0; j < current_ring_multiplier; j++){
            row++; i++;
            check_end(&i, &col, &row);
        }

        
        for(int j = 0; j < current_ring_multiplier + 1; j++){
            col--; i++;
            check_end(&i, &col, &row);
        }

        
        for(int j = 0; j < current_ring_multiplier + 1; j++){
            row--; i++;
            check_end(&i, &col, &row);
        }

        
        for(int j = 0; j < current_ring_multiplier + 1; j++){
            col++; i++;
            check_end(&i, &col, &row);
        }

        
        current_ring_multiplier += 2;
        col++; i++;
        check_end(&i, &col, &row);
    }

    return EXIT_SUCCESS;
}
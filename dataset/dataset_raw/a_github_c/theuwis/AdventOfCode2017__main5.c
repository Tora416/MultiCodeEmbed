#include <stdio.h>
#include <stdlib.h>

#define MAX_NR 10000
#define NR_OF_BANKS 16
int input[NR_OF_BANKS] = {4, 1, 15, 12, 0, 9, 9, 5, 5, 8, 7, 3, 14, 5, 12, 3};

int answers[MAX_NR][NR_OF_BANKS];

int main(void){
    int redistr_index, highest_nr_of_blocks = 0;

    
    for(int bank_index = 0; bank_index < NR_OF_BANKS; bank_index++){
        answers[0][bank_index] = input[bank_index];
    }

    
    for(int step = 1; step < MAX_NR; step++){
        
        for(int bank_index = 0; bank_index < NR_OF_BANKS; bank_index++){
            if(input[bank_index] > highest_nr_of_blocks){
                redistr_index = bank_index;
                highest_nr_of_blocks = input[bank_index];
            }
        }

        
        input[redistr_index] = 0;

        
        for(int i = 0; i < highest_nr_of_blocks; i++){
            redistr_index < NR_OF_BANKS - 1 ? (redistr_index++) : (redistr_index = 0);
            input[redistr_index]++;
        }
        highest_nr_of_blocks = 0;

        
        for(int bank_index = 0; bank_index < NR_OF_BANKS; bank_index++){
            answers[step][bank_index] = input[bank_index];
        }
    }

    
    int duplicate_found = 0;
    int occurence_found = 0;
    int occurence_found_index = 0;
    int q = 0;

    while(occurence_found == 0 && q < MAX_NR){
        for(int j = q + 1; j < MAX_NR; j++){
            for(int k = 0; k < NR_OF_BANKS; k++){
                if(answers[q][k] != answers[j][k]){
                    duplicate_found = 1;
                    break;
                }
            }

            if(duplicate_found == 0){
                printf("answer pt1=%d\n", j);
                occurence_found = 1;
                occurence_found_index = j;
                break;
            }

            duplicate_found = 0;
        }

        q++;
    }

    for(int q = occurence_found_index + 1; q < MAX_NR; q++){
        for(int k = 0; k < NR_OF_BANKS; k++){
            if(answers[occurence_found_index][k] != answers[q][k]){
                duplicate_found = 1;
                break;
            }
        }

        if(duplicate_found == 0){
            printf("answer pt2=%d\n", q - occurence_found_index);
            exit(EXIT_SUCCESS);
        }
        duplicate_found = 0;
    }

    return EXIT_SUCCESS;
}

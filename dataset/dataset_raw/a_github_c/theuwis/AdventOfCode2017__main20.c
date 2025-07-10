#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NR_OF_COLS 16

int main(void){
    long answer = 0;
    int numbers[NR_OF_COLS], numbers_index = 0;

    FILE * fp_data;
    if(!(fp_data = fopen("data", "r"))){
        fprintf(stderr, "Error opening file\n");
        return EXIT_FAILURE;
    }

    char * data_read = NULL, * curr_number;
    size_t len = 0;
    ssize_t read;

    while((read = getline(&data_read, &len, fp_data)) != -1){
        
        
        curr_number = strtok(data_read, "\t");
        while(curr_number != NULL){
            numbers[numbers_index] = atoi(curr_number);
            numbers_index++;
            curr_number = strtok(NULL, "\t");
        }

        numbers_index = 0;

        
        for(int i = 0; i < NR_OF_COLS; i++){
            for(int j = i + 1; j < NR_OF_COLS; j++){
                if(numbers[i] % numbers[j] == 0){
                    answer += (numbers[i] / numbers[j]);
                    break;
                }
                else if(numbers[j] % numbers[i] == 0){
                    answer += (numbers[j] / numbers[i]);
                    break;
                }
            }
        }
    }

    printf("answer=%ld\n", answer);

    free(data_read);
    free(curr_number);
    fclose(fp_data);
    return EXIT_SUCCESS;
}
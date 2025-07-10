#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void){
    long answer = 0;
    int small_nr = 99999, large_nr = 0, curr_number_int = 0;

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
            curr_number_int = atoi(curr_number);
            
            
            if(curr_number_int < small_nr){
                small_nr = curr_number_int;
            }
            if(curr_number_int > large_nr){
                large_nr = curr_number_int;
            }
            curr_number = strtok(NULL, "\t");
        }

        answer += (large_nr - small_nr);
        small_nr = 99999;
        large_nr = 0;
    }

    printf("answer=%ld\n", answer);

    free(data_read);
    free(curr_number);
    fclose(fp_data);
    return EXIT_SUCCESS;
}
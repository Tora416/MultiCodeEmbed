#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void){
    FILE *fp;
    if(!(fp = fopen("data", "r"))){
        fprintf(stderr, "Error opening file\n");
        return EXIT_FAILURE;
    }

    char current_char, next_char;       
    long answer = 0;                        

    
    while((next_char = fgetc(fp)) != EOF) {
        if(current_char == next_char){
            answer += (current_char - '0'); 
        }

        current_char = next_char;
    }

    
    
    fseek(fp, 0, SEEK_SET);
    current_char = fgetc(fp);
    fseek(fp, -1, SEEK_END);
    next_char = fgetc(fp);

    if(current_char == next_char){
        answer += (current_char - '0');
    }

    printf("answer=%ld\n", answer);

    fclose(fp);
    return EXIT_SUCCESS;
}
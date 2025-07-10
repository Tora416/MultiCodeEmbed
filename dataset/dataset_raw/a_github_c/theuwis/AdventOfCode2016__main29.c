#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DATA_TO_FILL 35651584

char input[60000000] = "11110010111001001";
char dummy[60000000], checksum[60000000];


int main(void){
    
    while(strlen(input) < DATA_TO_FILL){
        int len = strlen(input);

        
        input[len - 1] = '0';

        
        for(int i = len, j = len; i >= 0; i--, j++){
            if(input[i] == '0'){
                input[j] = '1';
            }
            else{
                input[j] = '0';
            }

        }
    }

    
    input[DATA_TO_FILL] = '\0';
    strcpy(checksum, input);
    
    
    while((strlen(checksum))%2 == 0){
        memset(dummy, 0, sizeof(dummy));

        int len = strlen(checksum);
        for(int i = 0, j = 0; i < len; i += 2, j++){
            if(checksum[i] == checksum[i + 1]){
                dummy[j] = '1';
            }
            else{
                dummy[j] = '0';
            }
        }
        strcpy(checksum, dummy);
    }

    printf("checksum=%s (len=%ld)\n", checksum, strlen(checksum));

    return EXIT_SUCCESS;
}

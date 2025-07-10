#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <stdbool.h>


int main(void){
    int num1, num2, product, i, str_len, answer;
    char numb_str[18];
    bool palindromic = true;

    for(num1 = 0; num1 < 1000; num1++){
        for(num2 = 0; num2 < 1000; num2++){
            product = num1 * num2;

            
            sprintf(numb_str, "%d", product);
            str_len = strlen(numb_str);

            
            for(i = 0; i < str_len / 2; i++){
                if(numb_str[i] != numb_str[str_len - 1 - i]){
                    palindromic = false;
                    break;
                }
            }

            
            
            if(palindromic && product > answer){
                answer = product;
            }

            palindromic = true;
        }
    }
    
    printf("answer=%d\n", answer);
    return EXIT_SUCCESS;
}
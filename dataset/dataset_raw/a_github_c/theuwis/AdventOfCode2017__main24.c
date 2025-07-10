#include <stdio.h>
#include <stdlib.h>

int main(void){
    long a = 722, b = 354;
    char a_hex[100], b_hex[100];
    int answer = 0;

    for(int i = 0; i < 5000000; i++){
        do{
            a *= 16807;
            a = a % 2147483647;
        }while(a % 4 != 0);

        do{
            b *= 48271;
            b = b % 2147483647;
        }while(b % 8 != 0);

        sprintf(a_hex, "%020X", (int) a);
        sprintf(b_hex, "%020X", (int) b);

        int diff_flag = 0;
        for(int i = 16; i < 20; i++){
            if(a_hex[i] != b_hex[i]){
                diff_flag = 1;
            }
        }

        (diff_flag == 0) ? (answer++) : (diff_flag = 0);
    }

    printf("answer=%d\n", answer);

    return EXIT_SUCCESS;
}

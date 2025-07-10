#include <stdio.h>
#include <stdlib.h>

int main(void){
    long a = 722, b = 354;
    char a_hex[100], b_hex[100];
    int answer = 0;

    for(int i = 0; i < 40000000; i++){
        a *= 16807;
        b *= 48271;

        a = a % 2147483647;
        b = b % 2147483647;

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



#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mulprec.h"

int simpleMultiple(int, int, int *);

int main(int argc, char **argv)
{
    int a = -5;
    int b = -3;
    int c, return_val;

    return_val = simpleMultiple(a, b, &c);
    printf("c = %d\n",c);
    printf("戻り値 = %d", return_val);

    return 0;
}


int simpleMultiple(int a, int b, int *c) {
    int i = 1;
    int tmp;
    int flag_a = 0; 
    int flag_b = 0; 

    if(a < 0){
        a = abs(a);
        flag_a++;
    } else if(b < 0){
        b = abs(b);
        flag_b++;
    }

    if(a < b){
        tmp = a;
        a = b;
        b = tmp;
    }

    *c = a;

    while(1){
        *c += a;
        i++;

        if(i == b){
            break;
        }
    }

    if(flag_a != 0 && flag_b != 0){
        
    } else if(flag_a != 0){
        *c *= -1;
    } else if(flag_b != 0){
        *c *= -1;
    }

    return 0; 
}
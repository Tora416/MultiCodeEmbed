

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mulprec.h"

int factorial(struct NUMBER *, struct NUMBER *);

int main(int argc, char **argv)
{
    struct NUMBER a, b;
    int return_val;
    int x;

    x = 5;

    setInt(&a, x);

    return_val = factorial(&a, &b);
    dispNumberZeroSuppress(&b);
    printf("\n戻り値 = %d", return_val);

    return 0;
}


int factorial(struct NUMBER *a, struct NUMBER *b) {
    
    if(getSign(a) == -1){ 
        return -2;
    }

    struct NUMBER tmp1, tmp2, num;
    setInt(&num, 1);
    int flag = 0;

    clearByZero(b);

    while(1){
        if(flag == 0){
            flag++;
            increment(&num, &tmp1);
            multiple(&num, &tmp, b);
            copyNumber(&tmp, &num);
        } else {
            increment(&num, &tmp1);
            multiple(b, &tmp1, &tmp2);
            copyNumber(&tmp2, b);
        }

        if(numComp(&tmp1, a) == 0){ 
            break;
        }
    }

    return 0;

    
        
    
}
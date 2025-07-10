#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mulprec.h"

void tailCall(struct NUMBER *, struct NUMBER *, struct NUMBER *);
int factorial(struct NUMBER *, struct NUMBER *);

int main(int argc, char **argv)
{
    struct NUMBER a, b;
    int return_val;
    int x;

    x = 0;

    setInt(&a, x);

    printf("x = %d\n", x);
    return_val = factorial(&a, &b);
    dispNumberZeroSuppress(&b);
    printf("\n戻り値 = %d", return_val);

    return 0;
}


void tailCall(struct NUMBER *a, struct NUMBER *b, struct NUMBER *sofar){
    struct NUMBER one, tmp1, tmp2;
    setInt(&one, 1);
    if(numComp(a, &one) != 1){ 
        copyNumber(sofar, b);
    } else {
        multiple(a, sofar, &tmp1);
        decrement(a, &tmp2);
        tailCall(&tmp2, b, &tmp1); 
    }
}


int factorial(struct NUMBER *a, struct NUMBER *b) {
    if(isZero(a) != -1){ 
        setInt(b, 1);
        return 0;
    } else if(getSign(a) == -1){ 
        return -2;
    }

    struct NUMBER one;
    setInt(&one, 1);

    if(numComp(a, &one) == 0){ 
        setInt(b, 1);
        return 0;
    }

    clearByZero(b);

    tailCall(a, b, &one);

    return 0;

}


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mulprec.h"

int gcd(struct NUMBER *, struct NUMBER *, struct NUMBER *);

int main(int argc, char **argv)
{
    struct NUMBER a, b, c;
    int return_val;
    int x, y;

    x = 1357911;
    y = 246810;

    setInt(&a, x);
    setInt(&b, y);

    return_val = gcd(&a, &b, &c);
    dispNumberZeroSuppress(&c);
    printf("\n戻り値 = %d", return_val);

    return 0;
}


int gcd(struct NUMBER *a, struct NUMBER *b, struct NUMBER *c) {
    struct NUMBER tmp, at, bt;

    getAbs(a, &tmp);
    copyNumber(&tmp, a);
    copyNumber(&tmp, &at);
    getAbs(b, &tmp);
    copyNumber(&tmp, b);
    copyNumber(&tmp, &bt);
    clearByZero(c);

    if(isZero(a) != -1 && isZero(b) != -1){ 
        return 0;
    } else if(isZero(b) != -1) { 
        copyNumber(a, c);
        return 0;
    }

    while(isZero(&tmp) == -1){
        divide(a, b, c, &tmp);
        copyNumber(b, a);
        copyNumber(&tmp, b);
    }

    
    copyNumber(a, c);
    copyNumber(&at, a);
    copyNumber(&bt, b);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mulprec.h"

int divide(struct NUMBER *, struct NUMBER *, struct NUMBER *, struct NUMBER *);

int main(int argc, char **argv)
{
    struct NUMBER a, b, c, d;
    int return_val;
    int x, y;

    x = 5;
    y = 3;

    setInt(&a, x);
    setInt(&b, y);

    printf("x = %d\ny = %d\nx / y = %d\nx %% y = %d", x, y, x / y, x % y);

    return_val = divide(&a, &b, &c, &d);
    dispNumberZeroSuppress(&c);
    dispNumberZeroSuppress(&d);
    printf("\n戻り値 = %d", return_val);

    return 0;
}


int divide(struct NUMBER *a, struct NUMBER *b, struct NUMBER *c, struct NUMBER *d) {
    struct NUMBER m, n, p, q;

    clearByZero(c);
    clearByZero(d);

    if(isZero(b) != -1){ 
        return -1;
    }

    copyNumber(a, &n);

    while(1){
        if(numComp(&n, b) != -1){ 
            increment(c, &m);
            copyNumber(&m, c);
            sub(&n, b, &m);
            copyNumber(&m, &n);
        } else { 
            copyNumber(&n, d);
            break;
        }
    }

    return 0;
}
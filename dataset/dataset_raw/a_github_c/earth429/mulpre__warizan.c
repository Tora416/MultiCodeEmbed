#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mulprec.h"

int divide(struct NUMBER *, struct NUMBER *, struct NUMBER *, struct NUMBER *);

int main(int argc, char **argv)
{
    double t1 = time(NULL);
    struct NUMBER a, b, c, d;
    
    int x, y;
    int i;

    x = 100000000;
    y = 2;

    setInt(&a, x);
    setInt(&b, y);

    printf("x = %d\ny = %d\nx / y = %d\nx %% y = %d\n", x, y, x / y, x % y);
    dispNumberZeroSuppress(&a);
    puts("");
    dispNumberZeroSuppress(&b);
    puts("");

    divide(&a, &b, &c, &d);
    dispNumberZeroSuppress(&c);
    puts("");
    dispNumberZeroSuppress(&d);
    puts("");

    

    double t2 = time(NULL);
    printf("処理時間:%f\n", t2 - t1);
    return 0;
}


int divide(struct NUMBER *a, struct NUMBER *b, struct NUMBER *c, struct NUMBER *d) {
    struct NUMBER m, n, p, q;

    
    if(getSign(a) > 0 && getSign(b) < 0){ 
        getAbs(b, &p);
        divide(a, &p, c, d);
        setSign(c, -1);
        return 0; 
    } else if(getSign(a) < 0 && getSign(b) > 0){ 
        getAbs(a, &p);
        divide(&p, b, c, d);
        setSign(c, -1);
        setSign(d, -1);
        return 0; 
    } else if(getSign(a) < 0 && getSign(b) < 0) { 
        getAbs(a, &p);
        getAbs(b, &q);
        divide(&p, &q, c, d);
        setSign(d, -1);
        return 0; 
    }

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
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "mulprec.h"

int sqrt_newton(struct NUMBER *, struct NUMBER *);

int main(int argc, char **argv)
{
    struct NUMBER r1, ans, tmp;
    int i, j, r;
    double r2;

    srandom(time(NULL));

    for (i = 0; i < 10;i++){
        r = random();
        setInt(&r1, r);
        for (j = 0; j < 10;j++){
            mulBy10(&r1, &tmp);
            copyNumber(&tmp, &r1);
        }
        sqrt_newton(&r1, &ans);
        printf("r1:");
        dispNumberZeroSuppress(&ans);
        puts("");
        r2 = sqrt((double)r);
        printf("r2:%f\n", r2);
    }

    return 0;
}


int sqrt_newton(struct NUMBER *a, struct NUMBER *b) {
    struct NUMBER x, ox, tx, zero, one, two, quotient, sum, rest; 
    clearByZero(b);
    setInt(&zero, 0);
    setInt(&one, 1);
    setInt(&two, 2);

    quickDivide(a, &two, &x, &rest);
    if(isZero(&x) != -1 || numComp(&x, &one) == 0){ 
        copyNumber(a, b);
        return 0;
    }
    if (numComp(&x, &zero) == -1){ 
        return -1;
    }

    copyNumber(&x, &ox);
    

    while(1){
        copyNumber(&ox, &tx);
        copyNumber(&x, &ox);
        quickDivide(a, &ox, &quotient, &rest);
        add(&ox, &quotient, &sum);
        quickDivide(&sum, &two, &x, &rest);

        if(numComp(&x, &ox) == 0){ 
            break;
        }
        if(numComp(&x, &tx) == 0){ 
            if(numComp(&ox, &x) == -1){ 
                copyNumber(&ox, &x);
            }
            break;
        }
        
    }

    copyNumber(&x, b);
    return 0;
}
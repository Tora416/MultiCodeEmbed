#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "mulprec.h"

int curt(struct NUMBER *, struct NUMBER *);



        
        multiple(&ox, &two, &dx); 
        

int main(int argc, char **argv)
{
    struct NUMBER r1, ans, tmp;
    int j, r;
    

    srandom(time(NULL));

    r = 27;
    setInt(&r1, r);
    
    curt(&r1, &ans);
    printf("r:%d\nr1:", r);
    dispNumberZeroSuppress(&ans);
    puts("");

    

    return 0;
}


int curt(struct NUMBER *a, struct NUMBER *b) {
    struct NUMBER x, ox, tx, px, dx, zero, one, two, three, quotient, sum, rest; 
    setInt(&zero, 0);
    setInt(&one, 1);
    setInt(&two, 2);
    setInt(&three, 3);

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
        power(&ox, &two, &px); 
        quickDivide(a, &px, &quotient, &rest);
        multiple(&ox, &two, &dx); 
        add(&dx, &quotient, &sum);
        quickDivide(&sum, &three, &x, &rest);

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
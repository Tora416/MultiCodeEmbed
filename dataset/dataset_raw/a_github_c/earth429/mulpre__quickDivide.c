#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mulprec.h"

int quickDivide(struct NUMBER *, struct NUMBER *, struct NUMBER *, struct NUMBER *);

int main(int argc, char **argv)
{
    double t1 = time(NULL);
    struct NUMBER a, b, c, d;
    
    int x, y;
    

    x = 49585;
    y = 98;


    setInt(&a, x);
    setInt(&b, y);

    printf("x = %d\ny = %d\nx / y = %d\nx %% y = %d\n", x, y, x / y, x % y);

    quickDivide(&a, &b, &c, &d);
    dispNumberZeroSuppress(&c);
    puts("");
    dispNumberZeroSuppress(&d);
    puts("");

    

    double t2 = time(NULL);
    printf("処理時間:%f\n", t2 - t1);
    
    return 0;
}


int quickDivide(struct NUMBER *a, struct NUMBER *b, struct NUMBER *c, struct NUMBER *d) {
    struct NUMBER tmp1, tmp2, a_tmp, e;

    if(isZero(b) != -1){ 
        return -1;
    }

    
    if(getSign(a) > 0 && getSign(b) < 0){ 
        getAbs(b, &tmp1);
        divide(a, &tmp1, c, d);
        setSign(c, -1);
        return 0; 
    } else if(getSign(a) < 0 && getSign(b) > 0){ 
        getAbs(a, &tmp1);
        divide(&tmp1, b, c, d);
        setSign(c, -1);
        setSign(d, -1);
        return 0; 
    } else if(getSign(a) < 0 && getSign(b) < 0) { 
        getAbs(a, &tmp1);
        getAbs(b, &tmp2);
        divide(&tmp1, &tmp2, c, d);
        setSign(d, -1);
        return 0; 
    }

    clearByZero(c); 
    copyNumber(a, &a_tmp);
    clearByZero(d);

    while(1){
        if(numComp(&a_tmp, b) >= 0){ 
            copyNumber(b, d); 
            setInt(&e, 1); 
            while(1){ 
                if(numComp(&a_tmp, d) >= 0){
                    mulBy10(d, &tmp1);
                    copyNumber(&tmp1, d);
                    mulBy10(&e, &tmp2);
                    copyNumber(&tmp2, &e);
                } else { 
                    divBy10(d, &tmp1); 
                    copyNumber(&tmp1, d);
                    divBy10(&e, &tmp2);
                    copyNumber(&tmp2, &e);
                    break;
                }
            }
            sub(&a_tmp, d, &tmp1); 
            copyNumber(&tmp1, &a_tmp);
            add(c, &e, &tmp2); 
            copyNumber(&tmp2, c);
            
            printf("c:");
            dispNumberZeroSuppress(c);
            puts("");
            printf("d:");
            dispNumberZeroSuppress(d);
            puts("");
            printf("a_tmp:");
            dispNumberZeroSuppress(&a_tmp);
            puts("");
        } else if(numComp(&a_tmp, b) < 0){ 
            copyNumber(&a_tmp, d);
            break; 
        }
    }

    return 0;
}
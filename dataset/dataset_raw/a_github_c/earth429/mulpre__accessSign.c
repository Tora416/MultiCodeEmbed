

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "mulprec.h"

int setSign(struct NUMBER *, int);
int getSign(struct NUMBER *);

int main(int argc, char **argv)
{
    struct NUMBER a;
    clearByZero(&a);
    dispNumberZeroSuppress(&a);
    setSign(&a, -1);
    dispNumberZeroSuppress(&a);

    return 0;
}


int setSign(struct NUMBER *a, int s) {
    if(s == 1){
        a->sign = 1;
    } else if(s == -1){
        a->sign = -1;
    } else {
        return -1;
    }

    return 0;
}


int getSign(struct NUMBER *a) {
    if(a->sign == 1){ 
        return 1;
    }
    
    return -1;
}
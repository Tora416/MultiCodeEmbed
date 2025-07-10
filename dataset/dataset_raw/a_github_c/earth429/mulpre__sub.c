

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mulprec.h"


int main(int argc, char **argv)
{
    struct NUMBER a, b, c;
    
    int x, y;

    x = 521;
    y = 23;

    setInt(&a, x);
    setInt(&b, y);

    printf("x = %d\ny = %d\nx - y = %d\n", x, y, x - y);
    sub(&a, &b, &c);
    dispNumberZeroSuppress(&c);

    

        

    return 0;
}


int sub(struct NUMBER *a, struct NUMBER *b, struct NUMBER *c) {
    int h = 0;
    int i;
    int return_val;
    int x, y; 
    struct NUMBER a_abs, b_abs; 

    clearByZero(c);

    if(getSign(a) > 0 && getSign(b) > 0){ 
        return_val = numComp(a, b); 

        switch (return_val)
        {
        case 1: 
            for (i = 0; i < KETA;i++){
                x = a->n[i] - h;
                y = b->n[i];
                if(x < y){
                    c->n[i] = 10 + x - y;
                    h = 1; 
                } else if(x >= y){
                    c->n[i] = x - y;
                    h = 0; 
                }
            }
            if(h != 0){ 
                return -1;
            }
            return 0; 
        case -1: 
            sub(b, a, c);
            setSign(c, -1);
            return 0;
        case 0: 
            return 0;
        }
    } else if(getSign(a) > 0 && getSign(b) < 0){ 
        getAbs(b, &b_abs);
        add(a, &b_abs, c);
        return 0; 
    } else if(getSign(a) < 0 && getSign(b) > 0){ 
        getAbs(a, &a_abs);
        add(&a_abs, b, c);
        setSign(c, -1);
        return 0; 
    } else if(getSign(a) < 0 && getSign(b) < 0){ 
        getAbs(b, &b_abs);
        add(a, &b_abs, c);
        return 0; 
    }

    return 100; 
}
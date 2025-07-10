

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mulprec.h"

int simpleDivide(int, int, int *, int *);

int main(int argc, char **argv)
{
    int a = 7;
    int b = -3;
    int c, d, return_val;

    return_val = simpleDivide(a, b, &c, &d);
    printf("c = %d\n", c);
    printf("d = %d\n", d);
    printf("戻り値 = %d", return_val);

    return 0;
}


int simpleDivide(int x, int y, int * z, int * w){
    int k;
    int x_abs, y_abs;

    if(y == 0){
        return -1;
    }

    if(x == 0){
        z = 0;
        w = 0;
        return 0;
    }
    
    if(x > 0 && y > 0){
        k = 0;
        while(1){
            if(x < y){
                break;
            }
            x -= y;
            k++;
        }
        *z = k; 
        *w = x; 
    } else if(x > 0 && y < 0){
        y_abs = abs(y);
        simpleDivide(x, y_abs, z, w);
        *z *= -1;
        *w *= -1;
    } else if(x < 0 && y > 0){
        x_abs = abs(x);
        simpleDivide(x_abs, y, z, w);
        *z *= -1;
        *w *= -1;
    } else {
        x_abs = abs(x);
        y_abs = abs(y);
        simpleDivide(x_abs, y_abs, z, w);
    }

    return 0;
}
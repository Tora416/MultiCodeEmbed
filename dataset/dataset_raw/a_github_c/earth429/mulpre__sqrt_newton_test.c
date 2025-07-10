

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int sqrt_newton(int);

int main(int argc, char **argv)
{
    int i, r, r1, r2, d;

    srandom(time(NULL));

    for (i = 0; i < 10;i++){
        r = random();
        r1 = sqrt_newton(r);
        r2 = (int)sqrt((double)r);
        d = r1 - r2;
        printf("%6d - %6d = %d\n", r1, r2, d);
    }

    return 0;
}

int sqrt_newton(int N) {
    int x;
    int b;
    int c;

    x = N / 2;
    if(x == 0){ 
        return N;
    }
    if(x < 0){ 
        return -1;
    }

    b = x;
    c = x;

    while(1){
        c = b;
        b = x;
        x = (b + (N / b)) / 2;

        if(x == b){ 
            break;
        }
        if(x == c){ 
            if(b < x){ 
                x = b;
            }
            break;
        }
    }

    return (x);
}
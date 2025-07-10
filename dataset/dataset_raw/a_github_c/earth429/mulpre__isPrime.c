

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mulprec.h"

int isPrime(struct NUMBER *);

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


int isPrime(struct NUMBER *a, struct NUMBER *b, struct NUMBER *c) {
    struct NUMBER tmp;
    
}
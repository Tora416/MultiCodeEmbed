#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mulprec.h"

int decrement(struct NUMBER *, struct NUMBER *);

int main(int argc, char **argv)
{
    struct NUMBER a, b;
    int return_val;

    setInt(&a, 1);

    return_val = decrement(&a, &b);
    dispNumberZeroSuppress(&a);
    dispNumberZeroSuppress(&b);
    printf("\n戻り値 = %d", return_val);

    return 0;
}


int decrement(struct NUMBER *a, struct NUMBER *b) {
    struct NUMBER one;
    int r;

    setInt(&one, 1);
    r = sub(a, &one, b);

    return r;
}
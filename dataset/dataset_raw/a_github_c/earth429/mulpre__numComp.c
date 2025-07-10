

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "mulprec.h"

int numComp(struct NUMBER *, struct NUMBER *);

int main(int argc, char **argv)
{
    struct NUMBER a, b;
    int return_val;

    srandom(time(NULL));

    clearByZero(&a);
    clearByZero(&b);

    return_val = numComp(&a, &b);
    printf("戻り値 = %d", return_val);

    setInt(&b, -1);
    return_val = numComp(&a, &b);
    printf("戻り値 = %d", return_val);

    setInt(&a, -1);
    return_val = numComp(&a, &b);
    printf("戻り値 = %d", return_val);

    return 0;
}


int numComp(struct NUMBER *a, struct NUMBER *b) {
    int sa = getSign(a);
    int sb = getSign(b);
    int i;

    if(sa > sb){ 
        return 1;
    }

    if(sa < sb){ 
        return -1;
    }

    if(sa == 1 && sb == 1){ 
        for (i = KETA - 1; i >= 0;i--){
            if(a->n[i] > b->n[i]){ 
                return 1;
            } else if(a->n[i] < b->n[i]){
                return -1;
            }
        }

        return 0; 
    }

    if(sa == -1 && sb == -1){ 
        for (i = KETA - 1; i >= 0;i--){
            if(a->n[i] > b->n[i]){ 
                return -1;
            } else if(a->n[i] < b->n[i]){
                return 1;
            }
        }

        return 0; 
    }

    
    return 100;
}
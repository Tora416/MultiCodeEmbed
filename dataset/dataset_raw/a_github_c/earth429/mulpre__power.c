
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "mulprec.h"

int power(struct NUMBER *, struct NUMBER *, struct NUMBER *);

int main(int argc, char **argv)
{
    struct NUMBER a, b, c;
    
    int x, y;
    int i;

    srandom(time(NULL));

    for (i = 0; i < TRY;i++){
        x = (random() % 10);
        y = (random() % 10);

        setInt(&a, x);
        setInt(&b, y);

        power(&a, &b, &c);
        

        setText(&c, pow(x, y));
        checkText();
    }

    

    return 0;
}


int power(struct NUMBER *a, struct NUMBER *b, struct NUMBER *c) {
    struct NUMBER i, tmp, i_tmp;
    setInt(&i, 1);
    clearByZero(c);

    if(isZero(b) != -1){ 
        setInt(c, 1);
        return 0;
    } else if(numComp(b, &i) == 0){ 
        copyNumber(a, c);
        return 0;
    }

    copyNumber(a, &tmp);

    while(1){
        
        if(numComp(&i, b) != -1){ 
            break;
        }
        multiple(a, &tmp, c);
        copyNumber(c, &tmp);

        increment(&i, &i_tmp);
        copyNumber(&i_tmp, &i);
    }

    return 0;
}
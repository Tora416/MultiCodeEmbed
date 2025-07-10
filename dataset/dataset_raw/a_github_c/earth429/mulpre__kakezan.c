#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mulprec.h"

int multiple(struct NUMBER *, struct NUMBER *, struct NUMBER *);

int main(int argc, char **argv)
{
    struct NUMBER a, b, c;
    
    int x, y;
    int i;

    srandom(time(NULL));

    for (i = 0; i < 10;i++){
        x = (random() % 1000);
        y = (random() % 1000);

        setInt(&a, x);
        setInt(&b, y);

        printf("x = %d\ny = %d\nx * y = %d\n", x, y, x * y);
        dispNumberZeroSuppress(&a);
        puts("");
        dispNumberZeroSuppress(&b);
        puts("");

        multiple(&a, &b, &c);
        setText(&c, x * y);
        checkText();
    }
        

    

    return 0;
}


int multiple(struct NUMBER *a, struct NUMBER *b, struct NUMBER *c) {
    int i, j, h, e, aj, bi;
    struct NUMBER a_abs, b_abs, d, tmp;

    clearByZero(c);

    if(getSign(a) > 0 && getSign(b) > 0){ 
        for (i = 0; i < KETA;i++){
            bi = b->n[i];
            h = 0;
            clearByZero(&d);
            for (j = 0; j < KETA;j++){
                aj = a->n[j];
                e = aj * bi + h; 
                if(j + i < KETA){ 
                    d.n[j + i] = (e % 10); 
                    e /= 10;
                    h = e; 
                }
                
            }
            if(h != 0){ 
                return -1;
            }
            add(c, &d, &tmp);
            copyNumber(&tmp, c);
        }
    } else if(getSign(a) > 0 && getSign(b) < 0){ 
        getAbs(b, &b_abs);
        multiple(a, &b_abs, c);
        setSign(c, -1);
    } else if(getSign(a) < 0 && getSign(b) > 0){ 
        getAbs(a, &a_abs);
        multiple(&a_abs, b, c);
        setSign(c, -1);
    } else if(getSign(a) < 0 && getSign(b) < 0){ 
        getAbs(a, &a_abs);
        getAbs(b, &b_abs);
        multiple(&a_abs, &b_abs, c);
    }

    return 0; 
}
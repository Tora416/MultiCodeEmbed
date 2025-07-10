

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mulprec.h"

int multiple(struct NUMBER *, struct NUMBER *, struct NUMBER *);

int main(int argc, char **argv)
{
    struct NUMBER a, b, c;
    int return_val;
int x, y;

    x = 16;
    y = 16;

    setInt(&a, x);
    setInt(&b, y);

    printf("x = %d\ny = %d\nx * y = %d\n", x, y, x * y);

    return_val = multiple(&a, &b, &c);
    printf("\n");
    dispNumberZeroSuppress(&c);
    printf("\n戻り値 = %d", return_val);

    return 0;
}


int multiple(struct NUMBER *a, struct NUMBER *b, struct NUMBER *c) {
    int i, j, h, e, aj, bi;
    struct NUMBER tmp, d;
    
    

    clearByZero(c);
    dispNumberZeroSuppress(a);
    dispNumberZeroSuppress(b);

    for (i = 0; i < KETA;i++){
        printf("iはここですよ%d\n", i);
        bi = b->n[i];
        h = 0;
        clearByZero(&d);
        for (j = 0; j < KETA;j++){
            aj = a->n[j];
            printf("aj:%d\nbi%d\n", aj, bi);
            
            
            
            
            
            e = aj * bi + h; 
            printf("e:%d\n", e); 
            if(j + i < KETA){
                d.n[j + i] = (e % 10); 
                printf("dl:");
                dispNumberZeroSuppress(&d);
                puts("");
                e /= 10;
                h = e; 
            }
        }

        if(h != 0){ 
            return -1;
        }
        printf("c:");
        dispNumberZeroSuppress(c);
        printf("d:");
        dispNumberZeroSuppress(&d);
        puts("");
        add(c, &d, &tmp);
        copyNumber(&tmp, c);
    }

    

    return 0; 
}
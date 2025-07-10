

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define KETA 15

struct NUMBER{
    int n[KETA]; 
    int sign; 
};

void dispNumberZeroSuppress(struct NUMBER *);

void dispNumber(struct NUMBER *a){
    int i;

    if(a->sign == 1){
        printf("+");
    } else {
        printf("-");
    }

    for (i = KETA - 1; i >= 0;i--){
        printf("%2d", a->n[i]);
    }
}


void clearByZero(struct NUMBER *a){
    int i;

    for (i = 0; i < KETA;i++){
        a->n[i] = 0;
    }

    a->sign = 1;
}


void setRnd(struct NUMBER *a, int k){
    int i;
    int judge;

    clearByZero(a);

    for (i = 0; i < k;i++){
        a->n[i] = random() % 10; 
    }

    judge = random() % 2; 

    switch (judge) {
        case 1:
            a->sign = 1;
            break;
        case 0:
            a->sign = -1;
            break;
    }
}

int main(int argc, char **argv)
{
    srandom(time(NULL));
    struct NUMBER a;

    setRnd(&a, 10);

    printf("a = "); 
    dispNumberZeroSuppress(&a);
    printf("\n");

    printf("aあり = "); 
    dispNumber(&a);
    printf("\n");

}


void dispNumberZeroSuppress(struct NUMBER *a){
    int i;

    if(a->sign == 1) {
        printf("+");
    } else {
        printf("-");
    }

    for (i = KETA - 1; i >= 0; i--) {
        if(a->n[i] != 0){
            
            break;
        }

        if(i == 0){
            
            printf("%2d", a->n[i]);
        }
    }
    for (; i >= 0;i--) {
        
        printf("%2d", a->n[i]);
    } 
}
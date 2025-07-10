#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mulprec.h"


void clearByZero(struct NUMBER *a){
    int i;

    for (i = 0; i < KETA;i++){
        a->n[i] = 0;
    }

    a->sign = 1;
}


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


void copyNumber(struct NUMBER *a, struct NUMBER *b){
    int i;

    clearByZero(b);

    b->sign = a->sign;

    for (i = 0; i < KETA;i++){
        b->n[i] = a->n[i];
    }
}


void getAbs(struct NUMBER *a, struct NUMBER *b){
    copyNumber(a, b);
    b->sign = 1; 
}


int isZero(struct NUMBER *a){
    int i;

    for (i = 0; i < KETA;i++){
        if(a->n[i] != 0){
            return -1;
        }
    }

    return 0;
}


int mulBy10(struct NUMBER *a, struct NUMBER *b){
    int i;

    clearByZero(b);

    b->sign = a->sign; 

    
    if(a->n[KETA - 1] != 0){
        return -1;
    }

    for (i = KETA - 2; i >= 0;i--){
        b->n[i + 1] = a->n[i];
    }

    

    b->n[0] = 0;

    return 0;
}


int divBy10(struct NUMBER *a, struct NUMBER *b){
    int i;
    int remainder; 

    clearByZero(b);

    b->sign = a->sign; 

    remainder = a->sign * a->n[0]; 

    for (i = 1; i <= KETA - 2;i++){
        b->n[i - 1] = a->n[i];
    }

    b->n[KETA - 1] = 0;

    return remainder;
}
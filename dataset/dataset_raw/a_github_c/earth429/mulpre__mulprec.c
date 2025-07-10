#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mulprec.h"


void clearByZero(struct NUMBER *a){
    int i;

    for (i = 0; i < KETA;i++){
        a->n[i] = 0;
    }

    setSign(a, 1);
}


void dispNumber(struct NUMBER *a){
    int i;

    if(getSign(a) == 1){
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

    if(getSign(a) == 1) {
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
            setSign(a, 1);
            break;
        case 0:
            setSign(a, -1);
            break;
    }
}


void copyNumber(struct NUMBER *a, struct NUMBER *b){
    int i;

    clearByZero(b);

    setSign(b, getSign(a));

    for (i = 0; i < KETA;i++){
        b->n[i] = a->n[i];
    }
}


void getAbs(struct NUMBER *a, struct NUMBER *b){
    copyNumber(a, b);
    setSign(b, 1); 
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

    setSign(b, getSign(a)); 

    
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

    setSign(b, getSign(a)); 

    remainder = getSign(a) * a->n[0]; 

    for (i = 1; i <= KETA - 2;i++){
        b->n[i - 1] = a->n[i];
    }

    b->n[KETA - 1] = 0;

    return remainder;
}


int setInt(struct NUMBER *a, int x) {
    int digit = 1; 
    int i;

    for (int i = x; i >= 10; i /= 10) { 
        digit++;
        if(digit > KETA) {
            return -1;
        }
    }

    clearByZero(a);

    if(x > 0){
        setSign(a, 1);
    } else {
        setSign(a, -1);
    }

    x = abs(x);

    for (i = 0; i < KETA;i++){
        a->n[i] = x % 10;
        x /= 10;
    }

    
    

    return 0;
}


void setText(struct NUMBER *a, int x) {
    FILE *fp;
    int i;

    if ((fp = fopen("check.txt", "a")) == NULL) {
        printf("ファイルをオープンできません。\n");
    } else {
        
        fprintf(fp, "%d\t", x);
        
        for (i = KETA - 1; i >= 0; i--) {
            if(getSign(a) != 0){
                break;
            }

            if(i == 0){
                fprintf(fp, "%d", a->n[i]);
            }
        }
        for (; i >= 0;i--) {
            fprintf(fp, "%d", a->n[i]);
        }
        fprintf(fp, "\n");

        fclose(fp);
    }
}


void checkText() {
    FILE *fp;
    int i;
    int int_num;
    int mul_num;

    if ((fp = fopen("check.txt", "r")) == NULL) {
        printf("ファイルをオープンできません。\n");
    } else {
        for (i = 0; i < TRY;i++){
            
            fscanf(fp, "%d", &int_num);
            
            fscanf(fp, "%d\n", &mul_num);

            if(int_num != mul_num){
                printf("値が違います\nint = %d\nmul = %d", int_num, mul_num);
            }
        }
        fclose(fp);
    }
    
}


int setSign(struct NUMBER *a, int s) {
    if(s == 1){
        a->sign = 1;
    } else if(s == -1){
        a->sign = -1;
    } else {
        return -1;
    }

    return 0;
}


int getSign(struct NUMBER *a) {
    if(a->sign == 1){ 
        return 1;
    }
    
    return -1;
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


int add(struct NUMBER *a, struct NUMBER *b, struct NUMBER *c) {
    int d; 
    int e = 0; 
    int i;
    struct NUMBER a_abs, b_abs; 

    clearByZero(c);

    if(getSign(a) > 0 && getSign(b) > 0){ 
        for (i = 0; i < KETA;i++){
            d = a->n[i] + b->n[i] + e;
            c->n[i] = d % 10;
            e = (d - c->n[i]) / 10; 
        }

        if(e != 0){ 
            return -1;
        }

    } else if(getSign(a) > 0 && getSign(b) < 0){ 
        getAbs(b, &b_abs);
        sub(a, &b_abs, c);
    } else if(getSign(a) < 0 && getSign(b) > 0){ 
        getAbs(a, &a_abs);
        sub(b, &a_abs, c);
    } else if(getSign(a) < 0 && getSign(b) < 0){ 
        getAbs(a, &a_abs);
        getAbs(b, &b_abs);
        add(&a_abs, &b_abs, c);
        setSign(c, -1);
    }

    return 0;
}


int sub(struct NUMBER *a, struct NUMBER *b, struct NUMBER *c) {
    int h = 0;
    int i;
    int return_val;
    int x, y; 
    struct NUMBER a_abs, b_abs; 

    clearByZero(c);

    if(getSign(a) > 0 && getSign(b) > 0){ 
        return_val = numComp(a, b); 

        switch (return_val)
        {
        case 1: 
            for (i = 0; i < KETA;i++){
                x = a->n[i] - h;
                y = b->n[i];
                if(a->n[i] < b->n[i]){
                    c->n[i] = 10 + x - y;
                    h = 1; 
                } else if(a->n[i] >= b->n[i]){
                    c->n[i] = x - y;
                    h = 0; 
                }
            }
            if(h != 0){ 
                return -1;
            }
            return 0; 
        case -1: 
            sub(b, a, c);
            setSign(c, -1);
            return 0;
        case 0: 
            return 0;
        }
    } else if(getSign(a) > 0 && getSign(b) < 0){ 
        getAbs(b, &b_abs);
        add(a, &b_abs, c);
        return 0; 
    } else if(getSign(a) < 0 && getSign(b) > 0){ 
        getAbs(a, &a_abs);
        add(&a_abs, b, c);
        setSign(c, -1);
        return 0; 
    } else if(getSign(a) < 0 && getSign(b) < 0){ 
        getAbs(b, &b_abs);
        add(a, &b_abs, c);
        return 0; 
    }

    return 100; 
}


int increment(struct NUMBER *a, struct NUMBER *b) {
    struct NUMBER one;
    int r;

    setInt(&one, 1);
    r = add(a, &one, b);

    return r;
}


int decrement(struct NUMBER *a, struct NUMBER *b) {
    struct NUMBER one;
    int r;

    setInt(&one, 1);
    r = sub(a, &one, b);

    return r;
}



int multiple(struct NUMBER *a, struct NUMBER *b, struct NUMBER *c) {
    int i, j, h, e, aj, bi;
    struct NUMBER tmp, d;
    int flag_a = 0; 
    int flag_b = 0; 

    clearByZero(c);

    for (i = 0; i < KETA;i++){
        bi = b->n[i];
        h = 0;
        clearByZero(&d);
        for (j = 0; j <= KETA;j++){
            aj = a->n[j];
            e = aj * bi + h; 
            d.n[j] = (e % 10); 
            e /= 10;
            h = (e % 10); 
            e /= 10;
            if(i == KETA && h != 0){ 
                return -1;
            }
        }
        add(c, &d, c);
    }

    

    return 0; 
}


int divide(struct NUMBER *a, struct NUMBER *b, struct NUMBER *c, struct NUMBER *d) {
    struct NUMBER m, n, p, q;

    clearByZero(c);
    clearByZero(d);

    if(isZero(b) != -1){ 
        return -1;
    }

    copyNumber(a, &n);

    while(1){
        if(numComp(&n, b) != -1){ 
            increment(c, &m);
            copyNumber(&m, c);
            sub(&n, b, &m);
            copyNumber(&m, &n);
        } else { 
            copyNumber(&n, d);
            break;
        }
    }

    return 0;
}
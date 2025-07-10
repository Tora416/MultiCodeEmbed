

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "mulprec.h"

int setInt(struct NUMBER *, int);
void setText(struct NUMBER *, int);
void checkText();
void dispNumberNormal(struct NUMBER *);

int main(int argc, char **argv)
{
    int i;
    srandom(time(NULL));
    struct NUMBER a;
    setInt(&a, -101);
    dispNumberZeroSuppress(&a);
    for (i = 0; i < TRY;i++){
        
        
        

        

        
        
        
        
    }
    
        

    return 0;
}


int setInt(struct NUMBER *a, int x) {
    int i;

    clearByZero(a);

    for (i = 0; i < KETA;i++){
        a->n[i] = x % 10;
        x = x / 10;
    }

    if(x > 0){
        setSign(a, 1);
    } else {
        setSign(a, -1);
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
            if(a->n[i] != 0){
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

            printf("int = %d\nmul = %d\n\n", int_num, mul_num);
        }

        fclose(fp);
    }
    
}


void dispNumberNormal(struct NUMBER *a){
    int i;

    
    for (i = KETA - 1; i >= 0; i--) {
        if(a->n[i] != 0){
            break;
        }

        if(i == 0){
            printf("%d", a->n[i]);
        }
    }
    for (; i >= 0;i--) {
        printf("%d", a->n[i]);
    } 
}


#include <stdio.h>
#include <math.h>


struct point {
    float re;
    float im;
};


struct point complex_add(struct point A, struct point B) {
    struct point C;
    C.re = A.re + B.re;
    C.im = A.im + B.im;
    return C;
}

int main(void) {
    struct point A, B, target;
    printf("Enter first number real and imaginary part of A = (a1 + ib1): ");
    scanf("%f %f", &A.re, &A.im);

    printf("Enter first number real and imaginary part of B = (a2 + ib2): ");
    scanf("%f %f", &B.re, &B.im);   

    target = complex_add(A, B);
    
    printf("A + B = %4.3f + i(%4.3f)\n", target.re, target.im);
    return 0;
}

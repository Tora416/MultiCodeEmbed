
#include <math.h>
#include <stdio.h>
#include <stdlib.h>


void findRoots(int a, int b, int c)
{
    if (a == 0) {
        printf("Invalid input, as a has to be non-zero.\n");
        return;
    }

    int d = b * b - 4 * a * c;
    double sqrt_val = sqrt(abs(d));

    if (d > 0) {
        printf("Roots are real and different \n");
        printf("%f\n%f", (double)(-b + sqrt_val) / (2 * a),
            (double)(-b - sqrt_val) / (2 * a));
    }
    else if (d == 0) {
        printf("Roots are real and same \n");
        printf("%f", -(double)b / (2 * a));
    }
    else 
    {
        printf("Roots are complex \n");
        printf("%f + i(%f)\n%f - i(%f)", -(double)b / (2 * a),
            sqrt_val, -(double)b / (2 * a), sqrt_val);
    }
}


int main()
{
    int a, b, c;
    printf("Give coefficients a, b and c in ax^2 + bx +c = 0 in order.\n");
    scanf("%d %d %d",&a,&b,&c);
    
    findRoots(a, b, c);
    return 0;
}


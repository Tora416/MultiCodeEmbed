

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int doubleSin(double *, double, int);
double factorial(double n) {
    if (n > 0) {
        return n * factorial(n - 1);
    } else {
        return 1;
    }
}

int main(int argc, char **argv)
{
    double a;
    double theta = 1.57;
    int n = 100;
    int return_val;

    return_val = doubleSin(&a, theta, n);
    printf("a = %f\ntheta = %f\n", a, theta);
    printf("sin = %f\n", sin(theta));
    printf("戻り値 = %d", return_val);

    return 0;
}


int doubleSin(double *a, double theta, int n) {
    int i;

    for (i = 0; i < n;i++){
        
        *a += pow(-1, i) / factorial(2 * i + 1) * pow(theta, 2 * i + 1);
        printf("now = %f\n", *a);
    }

    return 0;
}
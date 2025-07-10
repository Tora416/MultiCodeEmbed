

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int doubleCos(double *, double, int);
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
    double theta = 3.14;
    int n = 100;
    int return_val;

    return_val = doubleCos(&a, theta, n);
    printf("a = %f\ntheta = %f\n", a, theta);
    printf("cos = %f\n", cos(theta));
    printf("戻り値 = %d", return_val);

    return 0;
}


int doubleCos(double *a, double theta, int n) {
    int i;

    for (i = 0; i < n;i++){
        
        *a += pow(-1, i) / factorial(2 * i) * pow(theta, 2 * i);
        
    }

    return 0;
}
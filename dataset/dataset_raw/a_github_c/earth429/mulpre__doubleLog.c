

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int doubleLog(double *, double, int);

int main(int argc, char **argv)
{
    double a;
    double x = 4.0;
    int n = 1000;
    int return_val;

    return_val = doubleLog(&a, x, n);
    printf("a = %f\nx = %f\n", a, x);
    printf("log = %f\n", log(x));
    printf("戻り値 = %d", return_val);

    return 0;
}


int doubleLog(double *a, double x, int n) {
    int i;

    for (i = 0; i < n;i++){
        
        *a += 2 / (2 * i + 1) * pow((x - 1) / (x + 1), 2 * i + 1);
        
    }

    return 0;
}
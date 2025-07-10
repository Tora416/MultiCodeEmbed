

#include <stdio.h>
#include <math.h>

double newton(double);
double f(double);
double fdash(double);

int main(int argc, char *argv)
{
    double x;
    double x0;
    int i;

    for (i = -5; i <= 5;i++){
        x0 = (double)i;
        x = newton(x0);
        printf("x0 = %10.6lf, x = %10.6lf\n", x0, x); 
    }

    return 0;
}


double newton(double x0) {
    double x; 
    double b; 
    double e; 

    e = 1.e-7;
    x = x0;
    b = x0;

    while(1){
        b = x; 
        x = b - (f(b) / fdash(b));

        if(fabs(x - b) < e){ 
            break;
        }
    }

    return x;
}


double f(double x) {
    return (x * x * x - 9 * x);
}


double fdash(double x) {
    return (3 * x * x - 9.0);
}
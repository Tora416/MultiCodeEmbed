

#include <stdio.h>
#include <math.h>

int bisection(double, double, double *);
double f(double);
int sgn(double);

int main(int argc, char ** argv)
{
    double a, b; 
    double x; 
    int r; 

    a = 1.0;
    b = 4.0;
    r = bisection(a, b, &x);
    printf("x = %lf\n", x);
    printf("戻り値 = %d\n", r);

    return 0;
}


int bisection(double a,double b, double *x) {
    double e; 
    double d; 
    double fx; 
    int as, bs, cs; 

    e = 1.e-7;
    as = sgn(f(a)); 
    bs = sgn(f(b)); 

    if(as == bs){ 
        return -1; 
    }
    
    while(1){
        d = (a + b) / 2.0;
        fx = f(d);
        cs = sgn(fx);
        printf("now a = %lf\n", a);
        printf("now b = %lf\n", b);
        if(cs == as){
            a = d;
        }
        if(cs == bs){
            b = d;
        }
        if(fx == 0.0){ 
            break;
        }
        if(fabs(a - b) < e){ 
            break;
        }
    }

    *x = d;
    return 0;
}


double f(double x) {
    return (cos(x/2));
}


int sgn(double g) {
    if(g < 0.0){
        return -1;
    }
    if(g > 0.0){
        return 1;
    }
    return 0;
}
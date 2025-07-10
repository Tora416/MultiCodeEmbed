#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double f(double x){ 
    return x+cos(x);
}

void initial_value(double x[2] ){ 
    while( (f(x[0])>0 || f(x[1])<0) && (f(x[0])<0 || f(x[1])>0) ){
        x[0] += 100;
        x[1] -= 100;
    }
}

void dichotomy(double x[2] ){ 
    double c;
    while(1){
        c = (x[0] + x[1]) / 2;
        if(f(c)*f(x[0]) < 0) x[1] = c;
        else x[0] = c;
        if(fabs(x[0]-x[1])<0.0000000001){
            printf("x = %.10lf\n",c);
            exit(1);
        }
    }
}

int main(){ 
    double x[2] = { 0, 0};
    initial_value(x);
    dichotomy(x);
    return 0;
}

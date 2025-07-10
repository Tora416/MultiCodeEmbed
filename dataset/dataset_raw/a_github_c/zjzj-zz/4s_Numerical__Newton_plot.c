#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define eps (1.0e-11)
#define f(x) (x*x*2-8)
#define df(x) (x*4)

int main(){
    FILE *gp;
    double xn, xo;
    int i=0, max=100;

    gp = popen("gnuplot -persist", "w");
    fprintf(gp, "set yrange [-100: 1000]\n");
    fprintf(gp, "set xrange [-10: 60]\n");
    fprintf(gp, "plot x*x*2-8, 0\n");
    xo = (xn = 20) + 1;
    while(fabs(xn - xo) > eps && i < max){
        xo = xn;
        xn = xo - f(xo)/df(xo);
        fprintf(gp, "replot (%lf*4)*(x-%lf) + (%lf*%lf*2-8)\n", xo, xo, xo, xo);
        i++;
        printf("[round:%2d], x = %.10lf\n", i, xo);
    }
    pclose(gp);
    if(i == max) printf("Not found answer.\n");
    else printf("%.10lf\n", xo);
    return 0;
}

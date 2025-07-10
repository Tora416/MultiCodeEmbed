#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define eps (1.0e-11)
#define f(x) (log(x)-1)
#define df(x) (1/x)

int main(){
    FILE *gp;
    double xn, xo;
    int i=0, max=100;

    gp = popen("gnuplot -persist", "w");
    fprintf(gp, "set yrange [-2: 2]\n");
    fprintf(gp, "set xrange [0.5: 5]\n");
    fprintf(gp, "plot log(x)-1, 0\n");
    xo = (xn = 1) + 1;
    while(fabs(xn - xo) > eps && i < max){
        xo = xn;
        xn = xo - f(xo)/df(xo);
        fprintf(gp, "replot (1/%lf)*(x-%lf) + (log(%lf)-1)\n", xo, xo, xo);
        i++;
        printf("[round:%2d], x = %.10lf\n", i, xo);
    }
    pclose(gp);
    if(i == max) printf("Not found answer.\n");
    else if(i == 1) printf("Not found answer.\n");
    else printf("%.10lf\n", xo);
    return 0;
}

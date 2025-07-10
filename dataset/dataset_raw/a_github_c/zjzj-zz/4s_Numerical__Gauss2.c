
#include <stdio.h>
#include <math.h>
#define error 0.0000000001 
#define N 2 

int main(){
    double a[N][N] = { { 4.0, 2.0 }, { 4.0, 5.0 } };
    double b[N] = { 2.0, -7.0 };
    double x[N], y[N];
    int i, j, k;

    for( i = 0; i < N; i++ ) x[i]=1.0;
    for( i = 0; i < 30; i++ ){
        for( j = 0; j < N; j++ ){
            for( k = 0; k < N; k++ ) y[k] = x[k];
            x[j] = ( (a[j][j] * y[j]) + b[j] );
            for( k = 0; k < N; k++ ){
                x[j] -= ( a[j][k] * y[k] );
            }
            x[j] /= a[j][j];
        }
        printf("[i=%2d]", i+1 );
        for( j = 0; j < N; j++ ){
            printf(" x%d = %.10f ", j+1, x[j]);
        } 
        printf("\n");
    }
    return 0;
}

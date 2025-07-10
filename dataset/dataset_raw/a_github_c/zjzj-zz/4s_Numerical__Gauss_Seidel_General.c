#include <stdio.h>
#include <math.h>
#define error 0.0000000001 
#define N 3 

int i, j, k;

void initial_value( double x[N] ){ 
    for( i = 0; i < N; i++ ) x[i] = 1.0;
}

void Seidel( double x[N], double  y[N], double a[N][N], double b[N]){ 
    for( j = 0; j < N; j++ ){
        for( k = 0; k < N; k++ ) y[k] = x[k];
        x[j] = ( (a[j][j] * y[j]) + b[j] );
        for( k = 0; k < N; k++ ) x[j] -= ( a[j][k] * y[k] );
        x[j] /= a[j][j];
    }
}

int Convergence_test( double x[N], double y[N] ){ 
    for( j = 0; j < N; j++ ){
        if( error < fabs( x[j] - y[j] ))return (1);
    }
    return (0);
}

int main(){ 
    double a[N][N] = { { 5.0, 1.0, 1.0 }, { 1.0, 4.0, 1.0 }, { 2.0, 1.0, 3.0 } }; 
    double b[N] = { 10.0, 12.0, 13.0 };
    double x[N], y[N];
    int c = 0;

    initial_value( x );

    while( Convergence_test( x, y) ){ 
        Seidel( x, y, a, b );
        c++; 
    }
    printf("[%3d週目] ", c ); 
    for( i = 0; i < N; i++) printf(" x%d = %.10f ", i+1, x[i] );
    printf("\n");
    return 0;
}

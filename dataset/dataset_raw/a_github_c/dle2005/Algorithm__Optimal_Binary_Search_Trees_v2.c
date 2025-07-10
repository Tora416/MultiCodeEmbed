#include <stdio.h>
#include <stdlib.h>

typedef int index;

float sum(int i, int j, float *p) {
    float result = 0;

    for(int k = i; k <= j; k++)
        result += p[k];

    return result;
}

int min(int i, int j, float **A, float *p) {
    int index;
    float min = 999;
    
    for(int k = i; k <= j; k++) {
        if(A[i][k-1] + A[k+1][j] + sum(i, j, p) < min) {
            min = A[i][k-1] + A[k+1][j] + sum(i, j, p);
            index = k;
        }
    }

    return index;
}

void optsearchtree(int n, float *p, float *minavg, index **R) {
    index i, j, k, diagonal;
    float **A = (float **)malloc(sizeof(float *) * (n + 2));
    for(int t = 0; t < n + 2; t++)
        A[t] = (float *)malloc(sizeof(float) * (n + 1));

    for(i = 1; i <= n; i++) {
        A[i][i-1] = 0;
        A[i][i] = p[i];
        R[i][i] = i;
        R[i][i-1] = 0;
    }

    A[n+1][n] = 0;
    R[n+1][n] = 0;

    for(diagonal = 1; diagonal <= n-1; diagonal++) {
        for(i = 1; i <= n - diagonal; i++) {
            j = i + diagonal;
            k = min(i, j, A, p);
            A[i][j] = A[i][k-1] + A[k+1][j] + sum(i, j, p);
            R[i][j] = k;
        }
    }

    printf("A = \n");
    for(int i = 1; i <= n + 1; i++) {
        for(int j = 0; j <= n; j++)
            printf("%.3f ", A[i][j]);
        printf("\n");
    }
    printf("\n");

    *minavg = A[1][n];
}

void main() {
    int n;
    float minavg;

    printf("n = ");
    scanf("%d", &n);
    printf("\n");

    float *p = (float *)malloc(sizeof(float) * (n + 1));
    int **R = (int **)malloc(sizeof(int *) * (n + 2));
    for(int i = 0; i < n + 2; i++)
        R[i] = (int *)malloc(sizeof(int) * (n + 1));

    for(int i = 1; i <= n; i++) {
        printf("Key[%d] = ", i);
        scanf("%f", &p[i]);
    }
    printf("\n");

    optsearchtree(n, p, &minavg, R);
    
    printf("minavg = %.3f\n\n", minavg);

    printf("R = \n");
    for(int i = 1; i <= n + 1; i++) {
        for(int j = 0; j <= n; j++)
            printf("%d ", R[i][j]);
        printf("\n");
    }
}

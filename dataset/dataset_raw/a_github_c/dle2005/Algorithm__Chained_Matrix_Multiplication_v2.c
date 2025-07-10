#include <stdio.h>
#include <stdlib.h>

typedef int index;

int **M;

int **init_matrix(int n) {
    int **matrix = (int **)malloc(sizeof(int *) * n);
    for(int i = 0; i < n; i++) {
        matrix[i] = (int *)malloc(sizeof(int) * n);
    }
    
    return matrix;
}

int minimum(int i, int j, int **M, int *d) {
    int min = 999, index = 0;

    for(int k = i; k <= j -1; k++) {
        if(M[i][k] + M[k+1][j] + d[i-1] * d[k] * d[j] < min) {
            min = M[i][k] + M[k+1][j] + d[i-1] * d[k] * d[j];
            index = k;
        }
    }
    return index;
}


int minmult(int n, int *d, int **P) {
    index i, j, k, diagonal;

    for(int i = 1; i <= n; i++)
        M[i][i] = 0;

    for(diagonal = 1; diagonal <= n - 1; diagonal++) {
        for(i = 1; i <= n - diagonal; i++) {
            j = i + diagonal;
            k = minimum(i, j, M, d);
            M[i][j] = M[i][k] + M[k+1][j] + d[i-1] * d[k] * d[j];
            P[i][j] = k;
        }
    }
    
    printf("M = \n");
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++)
            printf("%-4d", M[i][j]);
        printf("\n");
    }
    printf("\n");

    return M[1][n];
}

void order(index i, index j, int **P) {
    int k;

    if(i == j) printf("A%d ", i);
    else {
        k = P[i][j];
        printf("( ");
        order(i, k, P);
        order(k+1, j, P);
        printf(") ");
    }
}
        

void main() {
    int n;

    printf("n = ");
    scanf("%d", &n);
    printf("\n");

    int **A = init_matrix(n);
    int **P = init_matrix(n + 1);
    M = init_matrix(n + 1);

    int *d = (int *)malloc(sizeof(int) * (n + 1));

    for(int i = 0; i < n; i++) {
        printf("A%d = ", i);
        scanf("%d %d", &A[i][0], &A[i][1]);
    }
    printf("\n");
    
    d[0] = A[0][0];
    for(int i = 0; i < n; i++)
        d[i + 1] = A[i][1]; 

    printf("bestcase = %d\n\n", minmult(n, d, P));

    printf("P = \n");
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++)
            printf("%4d", P[i][j]);
        printf("\n");
    }
    printf("\n");

    printf("order = ");
    order(0, n, P);
    printf("\n");

    printf("\n");
    for(int diagonal = 1; diagonal <= n - 1; diagonal++) {
        for(int i = 1; i <= n - diagonal; i++) {
            int j = i + diagonal;
            printf("M[%d][%d] = ", i, j);
            order(i, j, P);
            printf("= %d\n", M[i][j]);
        }
        printf("\n");
    }
}

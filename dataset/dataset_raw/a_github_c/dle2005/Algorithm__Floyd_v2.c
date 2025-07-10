#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void floyd2(int n, int **W, int **D, int **P) {
    int i, j, k; 

    for(i = 0; i <= n; i++) 
        for(j = 0; j <= n; j++) 
            P[i][j] = 0;

    for(i = 0; i <= n; i++) 
        for(j = 0; j <= n; j++) 
            D[i][j] = W[i][j]; 

    for(k = 1; k <= n; k++) 
        for(i = 1; i <= n; i++)
            for(j = 1; j <= n; j++)
                if(D[i][k] + D[k][j] < D[i][j]) { 
                    P[i][j] = k; 
                    D[i][j] = D[i][k] + D[k][j]; 
                }
}

void path(int q, int r, int **P) {
    if(P[q][r] != 0) { 
        path(q, P[q][r], P); 
        printf("v%d -> ", P[q][r]);
        path(P[q][r], r, P);
    }
}

int** init_matrix(int size) { 
    int **matrix = (int**)malloc(sizeof(int*) * size); 
    for(int i = 0; i < size; i++) {
        matrix[i] = (int*)malloc(sizeof(int) * size);
        memset(matrix[i], 0, sizeof(int)*size); 
    }

    return matrix;
}

void main() {

    int n = 5; 
    int **W = init_matrix(n + 1); 
    int **D = init_matrix(n + 1); 
    int **P = init_matrix(n + 1);

    for(int i = 1; i <= n; i++) 
        for(int j = 1; j <= n; j++)
            scanf("%d", &W[i][j]);

    floyd2(n, W, D, P); 

    printf("\n");
    for(int i = 1; i <= n; i++) { 
        for(int j = 1; j <= n; j++)
            printf("%d ", D[i][j]);
        printf("\n");
    }
        
    printf("\n");
    for(int i = 1; i <= n; i++) { 
        for(int j = 1; j <= n; j++)
            printf("%d ", P[i][j]);
        printf("\n");
    }
    
    printf("\n");
    for(int i = 1; i <= n; i++) { 
        for(int j = 1; j <= n; j++) {
            if(P[i][j] != 0) {
                printf("Path v%d ~ v%d: v%d -> ", i, j, i); 
                path(i, j, P);
                printf("v%d\n", j);
            }
        }
    }
}

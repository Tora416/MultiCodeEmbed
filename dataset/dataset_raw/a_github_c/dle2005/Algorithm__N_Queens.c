#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

int n;
int *col;

bool promising(int i) {
    bool swtch = true;
    int k = 1;
    
    while(k < i && swtch) {
        if(col[i] == col[k] || abs(col[i] - col[k]) == abs(i - k))
            swtch = false;
        k++;
    }
    return swtch;
}

void queens(int i) {
    for(int j = 1; j <= n; j++)
        printf("%d ", col[j]);
    printf("\n");

    if(promising(i)) {
        if(i == n) {
            printf("\nSolution = ");
            for(int j = 1; j <= n; j++)
                printf("%d ", col[j]);
            printf("\n");
            exit(1);
        }
        else {
            for(int j = 1; j <= n; j++) {
                col[i+1] = j;
                queens(i+1);
            }
        }
    }
}

void main() {
    
    printf("n = ");
    scanf("%d", &n);
    printf("\n");

    col = (int *)malloc(sizeof(int) * (n + 1));

    queens(0);

}

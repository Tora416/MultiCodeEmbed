#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

int n, *vindex, **W;
bool promising(int);

void hamiltonian(int i) {
    for(int j = 1; j <= n-1; j++)
        printf("%d ", vindex[j]);
    printf("\n");

    if(promising(i)) {
        if(i == n-1) {
            printf("vindex = ");
            for(int j = 1; j <= n-1; j++)
                printf("%d ", vindex[j]);
            printf("\n");
        }
        else {
            for(int j = 2; j <= n; j++) {
                vindex[i+1] = j;
                hamiltonian(i+1);
            }
        }
    }
}

bool promising(int i) {
    int j = 1;
    bool swtch;

    if(i == n-1 && !W[vindex[n-1]][vindex[0]])
        swtch = false;
    else if(i > 0 && !W[vindex[i-1]][vindex[i]])
        swtch = false;
    else {
        swtch = true;

        while(j < i && swtch) {
            if(vindex[i] == vindex[j]) swtch = false;
            j++;
        }
    }
    
    return swtch;
}

void main() {
    
    printf("n = ");
    scanf("%d", &n);
    printf("\n");

    W = (int **)malloc(sizeof(int *) * (n+1));
    for(int i = 0; i <= n; i++) {
        W[i] = (int *)malloc(sizeof(int) * (n+1));
        memset(W[i], 0, sizeof(int) * (n+1));
    }
    vindex = (int *)malloc(sizeof(int) * (n+1));
    vindex[0] = 1;

    printf("W = \n");
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= n; j++)
            scanf("%d", &W[i][j]);
    printf("\n");

    hamiltonian(0);
}


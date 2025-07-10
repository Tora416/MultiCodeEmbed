#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int W;
int *w, *include, *save;

bool promising(int i, int weight, int total) {
    if(! ((weight + total >= W) && (weight == W || weight + w[i+1] <= W))) {
        if(weight + total >= W) printf("weight + total >= W\n");
        else if(weight == W || weight + w[i+1] <= W) {
            if (!(weight + w[i+1] <= W)) printf("weight + w[i+1] <= W\n");
            else if(!(weight == W)) printf("weight == W\n");
        }
    }
    else if(weight == W) printf(" <- this is the solution\n");
    else printf("\n");

    return (weight + total >= W)
        && (weight == W || weight + w[i+1] <= W);
}

void sum_of_subsets(int i, int weight, int total) {
    printf("total: %d\n", total);
    for(int j = 1; j <= i; j++)
        printf("%d ", include[j]);

    if(promising(i, weight, total)) {
        if(weight == W) {
            for(int j = 1; j <= i; j++)
                save[i] = include[i];
        }
        else {
            include[i+1] = 1;
            sum_of_subsets(i+1, weight + w[i+1], total - w[i+1]);
            include[i+1] = 0;
            sum_of_subsets(i+1, weight, total - w[i+1]);
        }
    }
}

void main() {
    int n, total;

    printf("n = ");
    scanf("%d", &n);
    printf("W = ");
    scanf("%d", &W);
    printf("\n");

    w = (int *)malloc(sizeof(int) * (n+1));
    include = (int *)malloc(sizeof(int) * (n+1));
    save = (int *)malloc(sizeof(int) * (n+1));

    for(int i = 1; i <= n; i++) {
        printf("w[%d] : ", i);
        scanf("%d", &w[i]);
    }
    printf("\n");

    for(int i = 1; i <= n; i++) total += w[i];

    sum_of_subsets(0, 0, total);
}

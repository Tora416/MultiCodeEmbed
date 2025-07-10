#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int index;
#define YES 1
#define NO 0

int n, W, maxprofit, numbest;
int *bestset, *include, *p, *w;

bool promising(int, int, int);

void knapsack(index i, int profit, int weight) {
    printf("index\t = %d\n", i);
    printf("profit\t = %d\n", profit);
    printf("weight\t = %d\n", weight);

    if((weight <= W) && (profit > maxprofit)) {
        maxprofit = profit;
        numbest = i;
        for(int j = 1; j <= n; j++)
            bestset[j] = include[j];
        printf("maxprofit = %d\n", maxprofit);
    }

    if(promising(i, profit, weight)) {
        include[i+1] = YES;
        knapsack(i+1, profit+p[i+1], weight+w[i+1]);
        include[i+1] = NO;
        knapsack(i+1, profit, weight);
    }
}

bool promising(index i, int profit, int weight) {
    index j, k;
    int totweight;
    float bound;

    if(weight >= W) {
        printf("x\n");
        printf("\n");
        return false;
    }
    else {
        j = i+1;
        bound = profit;
        totweight = weight;
        while((j <= n) && (totweight + w[j] <= W)) {
            totweight = totweight + w[j];
            bound = bound + p[j];
            j++;
        }

        k = j;
        if(k <= n) 
            bound = bound + (W-totweight) * p[k] / w[k];
        printf("bound\t = %.0f\n", bound);

        if(bound > maxprofit) {
            printf("\n");
            return true;
        }
        else {
            printf("x\n\n");
            return false;
        }

        return bound > maxprofit;
    }
}


void main() {

    printf("n = ");
    scanf("%d", &n);
    printf("W = ");
    scanf("%d", &W);

    w = (int *)malloc(sizeof(int) * n + 1);
    p = (int *)malloc(sizeof(int) * n + 1);
    bestset = (int *)malloc(sizeof(int) * n + 1);
    include = (int *)malloc(sizeof(int) * n + 1);
    
    printf("w[1...n] = ");
    for(int i = 1; i <= n; i++)
        scanf("%d", &w[i]);
    printf("p[1...n] = ");
    for(int i = 1; i <= n; i++)
        scanf("%d", &p[i]);
    printf("\n");

    knapsack(0, 0, 0);

    printf("bestset[1..n] = ");
    for(int i = 1; i <= numbest; i++)
        printf("%d ", bestset[i]);
    printf("\n");

    free(w);
    free(p);
    free(bestset);
    free(include);
}

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 100

int n, *p, *w, W, maxprofit;

typedef struct node {
    int level;
    int profit;
    int weight;
    float bound;
} node;

int front = -1;
int rear = -1;
node queue[MAX];

bool empty() {
    if(front == rear) return true;
    else return false;
}

void insert(node v) {
    rear = rear+1;
    queue[rear].level = v.level;
    queue[rear].profit = v.profit;
    queue[rear].weight = v.weight;
    queue[rear].bound = v.bound;
}

void rmove(node *v) {
    front = front+1;
    v->level = queue[front].level;
    v->profit = queue[front].profit;
    v->weight = queue[front].weight;
    v->bound = queue[front].bound;
}

float bound(node u) {
    int j, k, totweight;
    float result;

    if(u.weight >= W) return 0;
    else {
        result = u.profit; j = u.level + 1; totweight = u.weight;
        while((j <= n) && (totweight + w[j] <= W)) {
            totweight = totweight + w[j];
            result = result + p[j];
            j++;
        }
        k = j;
        if(k <= n) result = result + (W - totweight) * p[k] / w[k];
        return result;
    }
}

void knapsack3() {
    node u, v;
    v.level = 0; v.profit = 0; v.weight = 0; v.bound = bound(v);
    maxprofit = 0;
    insert(v);
    
    while(!empty()) {
        rmove(&v);

        printf("%d profit: %3d weight: %3d bound: %3d maxprofit: %3d bound: %3d\n",
                v.level, v.profit, v.weight, (int)bound(v), maxprofit, (int)v.bound);

        if(v.bound > maxprofit) {
            u.level = v.level + 1;
            u.profit = v.profit + p[u.level];
            u.weight = v.weight + w[u.level];

            if((u.weight <= W) && (u.profit > maxprofit))
                maxprofit = u.profit;

            u.bound = bound(u);

            if(bound(u) > (float)maxprofit) insert(u);

            u.weight = v.weight;
            u.profit = v.profit;
            u.bound = bound(u);

            if(u.bound > (float)maxprofit) insert(u);
        }
    }
}
            




void main() {
    printf("n = ");
    scanf("%d", &n);
    printf("W = ");
    scanf("%d", &W);

    w = (int *)malloc(sizeof(int) * n + 1);
    p = (int *)malloc(sizeof(int) * n + 1);
    
    printf("w[1...n] = ");
    for(int i = 1; i <= n; i++)
        scanf("%d", &w[i]);
    printf("p[1...n] = ");
    for(int i = 1; i <= n; i++)
        scanf("%d", &p[i]);
    printf("\n");

    knapsack3();

    printf("maxprofit = %d\n", maxprofit);
}



















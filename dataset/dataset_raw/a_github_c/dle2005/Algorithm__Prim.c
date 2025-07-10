#include <stdio.h>
#include <stdlib.h>

typedef struct set_of_edges {
    int from;
    int end;
    int distance;
} edge;

int *nearest, *distance;

void prim(int n, int **W, edge *F) {
    int i, vnear, min;
    edge e;

    for(i = 2; i <= n; i++) {
        nearest[i] = 1;
        distance[i] = W[1][i];
    }

    printf("nearest = ");
    for(i = 2; i <= n; i++) printf("%d ", nearest[i]);
    printf("\ndistance = ");
    for(i = 2; i <= n; i++) printf("%d ", distance[i]);
    printf("\n\n");

    for(int j = 0; j < n -1; j++) {
        min = 999;
        for(i = 2; i <= n; i++) 
            if(0 <= distance[i] && distance[i] <= min) {
                min = distance[i];
                vnear = i;
            }
        
        e.from = nearest[vnear];
        e.end = vnear;
        e.distance = distance[vnear];

        F[j].from = e.from;
        F[j].end = e.end;
        F[j].distance = e.distance;

        distance[vnear] = -1;

        printf("path : V%d -> V%d distance %d\n\n", e.from, e.end, e.distance);

        for(i = 2; i <= n; i++)
            if(W[i][vnear] < distance[i]) {
                distance[i] = W[i][vnear];
                nearest[i] = vnear;
            }

        printf("nearest = ");
        for(i = 2; i <= n; i++) printf("%d ", nearest[i]);
        printf("\ndistance = ");
        for(i = 2; i <= n; i++) printf("%d ", distance[i]);
        printf("\n\n");

    }
}
void main() {
    int n = 0;

    printf("n = ");
    scanf("%d", &n);
    printf("\n");

    int **W = (int **)malloc(sizeof(int *) * (n + 1));
    for(int i = 0; i <= n; i++)
        W[i] = (int *)malloc(sizeof(int) * (n + 1));
    nearest = (int *)malloc(sizeof(int) * (n + 1));
    distance = (int *)malloc(sizeof(int) * (n + 1));
    edge *F = (edge *)malloc(sizeof(edge) * n);

    printf("W = \n");
    for(int i = 1; i <= n; i++) 
        for(int j = 1; j <= n; j++) 
            scanf("%d", &W[i][j]);
    printf("\n");

    prim(n, W, F);
}

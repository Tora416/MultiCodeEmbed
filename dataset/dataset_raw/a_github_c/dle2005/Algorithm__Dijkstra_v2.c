#include <stdio.h>
#include <stdlib.h>

#define INF 9999

typedef int number;
typedef int index;

typedef struct _Edge {
    int j;
    int touch;
    int length;
} edge;

typedef edge set_of_edges;

void dijkstra(int n, number **W, set_of_edges *F) {
    index i, vnear;
    edge e;
    index touch[n];
    number length[n];

    for(i = 1; i < n; i++) {
        touch[i] = 1;
        length[i] = W[0][i];
    }

    for(int j = 0; j < n-1; j++) {
        int min = INF;
        for(i = 1; i < n; i++) {
            if(0 <= length[i] && length[i] <= min) {
                min = length[i];
                vnear = i;
            }
        }
        
        e.j = vnear;
        e.touch = touch[vnear];
        e.length = length[vnear];

        F[vnear].j = e.j;
        F[vnear].touch = e.touch;
        F[vnear].length = e.length;

        
        for(i = 1; i < n; i++) {
            if(length[vnear] + W[vnear][i] < length[i]) {
                length[i] = length[vnear] + W[vnear][i];
                touch[i] = vnear + 1;
            }
        }
        length[vnear] = -1;
    }
}

int main() {
    int num_of_Vertex;

    printf("-----input-----\n");
    printf("num of Vertex = ");
    scanf("%d", &num_of_Vertex);

    edge F[num_of_Vertex];
    number **W = (int **)malloc(sizeof(int) * num_of_Vertex);
    for(int i = 0; i < num_of_Vertex; i++)
        W[i] = (int *)malloc(sizeof(int) * num_of_Vertex);

    printf("insert weight graph\n");
    for(int i = 0; i < num_of_Vertex; i++)
        for(int j = 0; j < num_of_Vertex; j++)
            scanf("%d", &W[i][j]);

    dijkstra(num_of_Vertex, W, F);

    printf("\n-----output-----\n");
    for(int i = 1; i < num_of_Vertex; i++) 
        printf("1 -> %d, length = %d, touch = %d\n",
                F[i].j + 1, F[i].length, F[i].touch);
}

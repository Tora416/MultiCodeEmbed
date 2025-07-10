#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef int set_pointer;

typedef struct _Edge {
    int ui;
    int uj;
    int distance;
} edge;
typedef edge set_of_edges;

typedef struct _Universe {
    int parent;
    int depth;
} universe;
universe *U;

void makeset(int i) {
    U[i].parent = i;
    U[i].depth = 0;
}

set_pointer find(int i) {
    int j;
    j = i;
    while(U[j].parent != j)
        j = U[j].parent;

    return j;
}

void merge(set_pointer p, set_pointer q) {
    if(U[p].depth == U[q].depth) {
        U[p].depth += 1;
        U[q].parent = p;
    }
    else if(U[p].depth < U[q].depth) U[p].parent = q;
    else U[q].parent = p;
}

bool equal(set_pointer p, set_pointer q) {
    if(p == q) return true;
    else return false;
}

void initial(int n) {
    int i;
    for(i = 0; i < n; i++) makeset(i);
}

int compare(const void *a, const void *b) {
    edge *u = (edge *)a;
    edge *v = (edge *)b;

    if(u->distance < v->distance) return -1;
    if(u->distance > v->distance) return 1;
    return 0;
}

int num_of_Vertex, num_of_Edges;
void kruskal(int n, int m, set_of_edges *E, set_of_edges *F) {
    int i, j;
    set_pointer p, q;
    edge e;

    qsort(E, num_of_Edges, sizeof(edge), compare);
    initial(num_of_Vertex);

    while(n < num_of_Vertex) {
        e.ui = E[m].ui;
        e.uj = E[m].uj;
        e.distance = E[m].distance;

        i = e.ui;
        j = e.uj;

        p = find(i);
        q = find(j);

        if(!equal(p, q)) {
            merge(p, q);
            F[n-1].ui = e.ui;
            F[n-1].uj = e.uj;
            F[n-1].distance = e.distance;

            n++;
        }

        m++;
    }
}

int main() {
   printf("-----input-----\n");
   printf("num of Vertex = ");
   scanf("%d", &num_of_Vertex);
   printf("num of Edges = ");
   scanf("%d", &num_of_Edges);

   U = (universe *)malloc(sizeof(universe) * num_of_Vertex);
   edge *E = (edge *)malloc(sizeof(edge) * num_of_Edges);
   edge *F = (edge *)malloc(sizeof(edge) * num_of_Edges);

   for(int i = 0; i < num_of_Edges; i++) {
       printf("insert edge = ");
       scanf("%d %d %d", &E[i].ui, &E[i].uj, &E[i].distance);
   }

   kruskal(1, 0, E, F);

   int value = 0; 
   printf("\n-----output-----\n");
   for(int i = 0; i < num_of_Vertex -1; i++) {
        printf("v%d - v%d = %d\n", F[i].ui, F[i].uj, F[i].distance);
        value += F[i].distance;
   }
   printf("minimum spannig tree value = %d\n", value);
}























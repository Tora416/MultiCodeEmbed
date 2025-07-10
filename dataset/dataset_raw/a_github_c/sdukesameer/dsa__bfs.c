
#include<stdio.h>
#include<stdlib.h>
typedef struct{
    int n;
    int** arr;
}graph;
typedef struct{
    int end;
    int* items;
}queue;
void input(graph* g){
    int i,j,f,x=1;
    while(x){
        printf("\nEnter the number of vertices: ");
        scanf("%d",&g->n);
        if(g->n>0)
            x=0;
        else
            printf("Invalid input. Try again.\n");
    }
    g->arr=(int**) malloc(sizeof(int*)*g->n);
    for(i=0;i<g->n;i++)
        g->arr[i]=(int*)malloc(sizeof(int)*g->n);
    for(i=0;i<g->n;i++)
        for(j=0;j<g->n;j++)
            g->arr[i][j]=-1;
    for(i=0;i<g->n;i++)
        for(j=0;j<g->n;j++){
            if(g->arr[i][j]==1 || g->arr[i][j]==0)
                continue;
            if(i==j){
                g->arr[i][j]=0;
                continue;
            }
            x=1;
            while(x){
                printf("Is there an edge between %c and %c (Yes=1 & No=0): ",'A'+i,'A'+j);
                scanf("%d",&f);
                if(f==0 || f==1){
                    g->arr[i][j]=f;
                    g->arr[j][i]=f;
                    x=0;
                }
                else
                    printf("Invalid input. Try again.\n");
            }
        }
}
void initialiseQueue(queue* q, int n){
    q->end=-1;
    q->items=(int*) malloc(sizeof(int)*n);
}
void enqueue(queue* q, int n){
    q->items[++(q->end)]=n;
}
int dequeue(queue* q){
    int ret=q->items[0];
    for(int i=0; i<q->end; i++)
        q->items[i]=q->items[i+1];
    q->end--;
    return ret;
}
void bfs(graph g, int s){
    queue q;
    initialiseQueue(&q,g.n);
    int visited[g.n],i,f;
    for(i=0;i<g.n;i++)
        visited[i]=0;
    visited[s]=1;
    enqueue(&q,s);
    printf("\nFollowing is the BFS Traversal (starting from %c): \n",'A'+s);
    while(q.end!=-1){
        f=dequeue(&q);
        printf("%c\t",'A'+f);
        for (i = 0; i < g.n; i++)
            if(g.arr[f][i])
                if(!visited[i]){
                    visited[i]=1;
                    enqueue(&q,i);
                }
    }
}
void free_graph(graph* g){
    for(int i=0; i<g->n; i++)
        free(g->arr[i]);
    free(g->arr);
}
int main(){
    graph g;
    int f=1,s;
    input(&g);
    printf("\n\' If");
    for(int i=0; i<g.n;i++)
        printf(" %c=%d",'A'+i,i+1);
    printf(" \'\nEnter the initial vertex: ");
    while(f){
        scanf("%d",&s);
        if(s>0 && s<g.n+1)
            f=0;
        else
            printf("Invalid input. Try again.\n");
    }
    bfs(g,s-1);
    free_graph(&g);
}
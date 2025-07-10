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
typedef struct{
    int top;
    int* items;
}stack;
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
void initialiseStack(stack* s, int n){
    s->top=-1;
    s->items=(int*)malloc(sizeof(int)*n);
}
void enqueue(queue* q, int n){
    q->items[++(q->end)]=n;
}
void push(stack* s, int n){
    s->items[++(s->top)]=n;
}
int dequeue(queue* q){
    int ret=q->items[0];
    for(int i=0; i<q->end; i++)
        q->items[i]=q->items[i+1];
    q->end--;
    return ret;
}
void pop(stack* s){
    s->top--;
}
int peek(stack* s){
    return s->items[s->top];
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
void dfs(graph g, int x){
    stack s;
    initialiseStack(&s,g.n);
    int visited[g.n],i,f,t;
    for(i=0;i<g.n;i++)
        visited[i]=0;
    printf("\nFollowing is the DFS Traversal (starting from %c): \n",'A'+x);
    visited[x]=1;
    printf("%c\t",'A'+x);
    push(&s,x);
    while(s.top!=-1){
        f=peek(&s);
        t=1;
        for(i=0; i<g.n; i++)
            if(g.arr[f][i])
                if(!visited[i]){
                    visited[i]=1;
                    printf("%c\t",'A'+i);
                    push(&s,i);
                    t=0;
                    break;
                }
        if(t)
            pop(&s);
    }
}
void free_graph(graph* g){
    for(int i=0; i<g->n; i++)
        free(g->arr[i]);
    free(g->arr);
}
int main(){
    graph g;
    input(&g);
    while(1){
        int f=1,s,ch=1;
        printf("\n\n****************\n");
        printf("1. BFS Traversal\n");
        printf("2. DFS Traversal\n");
        printf("3. EXIT\n");
        printf("Select the traversal you want to execute: ");
        scanf("%d",&ch);
        if(ch==1){
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
        }
        else if(ch==2){
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
            dfs(g,s-1);
        }
        else if(ch==3)
            break;
        else
            printf("\nInvalid input. Try again.\n");
    }
    printf("\nExitting program. Thank You.\n");
    free_graph(&g);
}
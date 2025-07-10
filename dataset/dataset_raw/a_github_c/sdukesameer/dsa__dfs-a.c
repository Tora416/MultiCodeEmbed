#include<stdio.h>
#include<stdlib.h>
typedef struct{
    int n;
    int** mat;
}gph;
typedef struct{
    int top;
    int* items;
}stk;
void input(gph* g){
    int i,j,f,x=1;
    while(x){
        printf("\nEnter the number of vertices: ");
        scanf("%d",&g->n);
        if(g->n>0)
            x=0;
        else
            printf("Invalid input.\n");
    }
    g->mat=(int**) malloc(sizeof(int*)*g->n);
    for(i=0;i<g->n;i++)
        g->mat[i]=(int*)malloc(sizeof(int)*g->n);
    for(i=0;i<g->n;i++)
        for(j=0;j<g->n;j++)
            g->mat[i][j]=-1;
    for(i=0;i<g->n;i++)
        for(j=0;j<g->n;j++){
            if(g->mat[i][j]==1 || g->mat[i][j]==0)
                continue;
            if(i==j){
                g->mat[i][j]=0;
                continue;
            }
            x=1;
            while(x){
                printf("Is there an edge between %c and %c (Yes=1 & No=0): ",'A'+i,'A'+j);
                scanf("%d",&f);
                if(f==0 || f==1){
                    g->mat[i][j]=f;
                    g->mat[j][i]=f;
                    x=0;
                }
                else
                    printf("Invalid input.\n");
            }
        }
}
void initialise(stk* s, int n){
    s->top=-1;
    s->items=(int*)malloc(sizeof(int)*n);
}
void push(stk* s, int n){
    s->items[++(s->top)]=n;
}
int peek(stk* s){
    return s->items[s->top];
}
void pop(stk* s){
    s->top--;
}
void dfs(gph g, int x){
    stk s;
    initialise(&s,g.n);
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
            if(g.mat[f][i])
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
void free_graph(gph* g){
    for(int i=0; i<g->n; i++)
        free(g->mat[i]);
    free(g->mat);
}
int main(){
    gph g;
    int f=1,x;
    input(&g);
    printf("\n\' If");
    for(int i=0; i<g.n;i++)
        printf(" %c=%d",'A'+i,i+1);
    printf(" \'\nEnter the initial vertex: ");
    while(f){
        scanf("%d",&x);
        if(x>0 && x<g.n+1)
            f=0;
        else
            printf("Invalid input.\n");
    }
    dfs(g,x-1);
    free_graph(&g);
}
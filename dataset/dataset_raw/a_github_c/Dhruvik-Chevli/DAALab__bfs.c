#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define FOR(i,a,b) for(ll i=a;i<b;i++)
typedef long long int ll;
struct Queue{
    int* arr;
    int front,rear;
    int cap,size;
};
struct Queue* createQueue(int cap)
{
    struct Queue* queue=(struct Queue*)malloc(sizeof(struct Queue));
    queue->front=-1;
    queue->rear=-1;
    queue->cap=cap;
    queue->size=0;
    queue->arr=(int*)malloc(cap*sizeof(int));
    return queue;
}
int isEmpty(struct Queue* queue)
{
    return (queue->size==0);
}
int isFull(struct Queue* queue)
{
    if (queue->size==queue->cap)
        return 1;
    return 0;
}
void enqueue(struct Queue* queue,int ele)
{
    if (isFull(queue))
    {
        
        return;
    }
    if (queue->front==-1)
    {
        queue->front=0;
    }
    queue->rear=(queue->rear+1)%queue->cap;
    queue->arr[queue->rear]=ele;
    queue->size++;
    
    return;
}
int dequeue(struct Queue* queue)
{
    if (isEmpty(queue))
        return -1;
    int ele=queue->arr[queue->front];
    if (queue->front==queue->rear)
    {
        queue->front=-1;
        queue->rear=-1;
    }
    queue->front=(queue->front+1)%queue->cap;
    queue->size--;
    return ele;
}
int** makeGraph(int v)
{
    int** graph=(int**)malloc(v*sizeof(int*));
    FOR(i,0,v)
    {
        graph[i]=(int*)malloc(v*sizeof(int));
    }
    FOR(i,0,v)
    {
        FOR(j,0,v)
        {
            graph[i][j]=0;
        }
    }
    int e;
    scanf("%d",&e);
    FOR(i,0,e)
    {
        int src, dest;
        scanf("%d %d",&src,&dest);
        graph[src][dest]=1;
        graph[dest][src]=1;
    }
    return graph;
}
void bfs(int** graph,int* visited,int v,int src)
{
    
    struct Queue* queue=createQueue(10000);
    enqueue(queue,src);
    int count=0;
    while(!isEmpty(queue))
    {
        
        int p=dequeue(queue);
        visited[p]=1;
        printf("%d ",p);
        
        count+=1;
        FOR(i,0,v)
        {
            if(graph[p][i])
            {
                if(!visited[i])
                {
                    
                    enqueue(queue,i);
                }
            }
        }
    }
    return;
}
int main()
{
    int v;
    scanf("%d",&v);
    int** graph=makeGraph(v);
    int* visited=(int* )malloc(v*sizeof(int));\
    FOR(i,0,v)
        visited[i]=0;
    
    FOR(i,0,v)
    {
        if(!visited[i])
        {
            bfs(graph,visited,v,i);
            printf("\n");
        }
    }
    return 0;
}
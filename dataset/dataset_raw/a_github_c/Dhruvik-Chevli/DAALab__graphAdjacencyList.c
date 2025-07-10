#include<stdio.h>
#include<stdlib.h>

struct adjLNode
{
    int dest;
    struct adjLNode* next;

};
struct adjList
{
    struct adjLNode* head;
};
struct Graph
{
    int V;
    struct adjList* arr;
};
struct Graph* createGraph(int V)
{
    struct Graph* graph=(struct Graph*)malloc(sizeof(struct Graph));
    graph->V=V;
    graph->arr=(struct adjList*)malloc(V*sizeof(struct adjList));
    for(int i=0;i<V;i++)
    {
        graph->arr[i].head=NULL;
    }
    return graph;
}
void addEdge(struct Graph* graph,int src,int dst)
{
    struct adjLNode* newNode=(struct adjLNode*)malloc(sizeof(struct adjLNode));
    newNode->dest=dst;
    newNode->next=graph->arr[src].head;
    graph->arr[src].head=newNode;
    struct adjLNode* newNode2=(struct adjLNode*)malloc(sizeof(struct adjLNode));
    newNode2->dest=src;
    newNode2->next=graph->arr[dst].head;
    graph->arr[dst].head=newNode2;

}
void printGraph(struct Graph* graph)
{
    for(int i=0;i<graph->V;i++)
    {
        struct adjLNode* temp=graph->arr[i].head;
        printf("The connected vertices to the vertex %d are- \n",i);
        while(temp)
        {
            printf("%d ",temp->dest);
            temp=temp->next;
        }
        printf("\n");
    }
}
int main()
{
    int V;
    printf("Please enter the number of vertices to your graph\n");
    scanf("%d",&V);
    struct Graph* graph=createGraph(V);
    int n;
    printf("Please enter the number of Edges you want the graph to have\n");
    scanf("%d",&n);
    for(int i=0;i<n;i++)
    {
        int src,dst;
        scanf("%d %d",&src,&dst);
        addEdge(graph,src,dst);
    }
    printGraph(graph);
    return 0;
}
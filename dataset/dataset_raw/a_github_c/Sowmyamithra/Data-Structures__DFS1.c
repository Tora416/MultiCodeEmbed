
#include<stdio.h>
#include<stdlib.h>
int STACK[100],top=-1;
void push(int x)
{
    if(top==99)
    printf("Stack isFull");
    else
    {
        top=top+1;
        STACK[top]=x;
    }
}
int pop()
{
    int x;
    if(top==-1)
    printf("\nStack is Empty");
    else
    {
        x=STACK[top];
        top=top-1;
        return(x);
    }
}
struct graph
{
    int val;
    struct graph* next;
}*G[10],*last;
void create(struct graph* G[],int n)
{
    int i,j,m,data;
    for(i=0;i<n;i++)
    {
        printf("\nenter the number of vertices adjacent to vertex %d :",i);
        scanf("%d",&m);
        for(j=0;j<m;j++)
        {
            printf("\nEnter the vertex to be inserted:");
            scanf("%d",&data);
            struct graph* p=(struct graph*)malloc(sizeof(struct graph));
            p->val=data;
            p->next=NULL;
            if(G[i]==NULL)
                G[i]=p;
            else
            {
                last=G[i];
                while(last->next!=NULL)
                    last=last->next;
                last->next=p;
            }
        }
    }
}
void display(struct graph* G[],int n)
{
    int i,j;
    for(i=0;i<n;i++)
    {
        last=G[i];
        printf("\nThe vertices adjacent to %d are :\n",i);
        while(last->next!=NULL)
        {
            printf("\t%d",last->val);
            last=last->next;
        }
        printf("\t%d",last->val);
    }
}
void main()
{
    int n,i,vertices[10],ct=0,v,visited[10]={1,1,1,1,1,1,1,1,1,1};
    printf("\nEnter the number of vertices of graph:");
    scanf("%d",&n);
    for(i=0;i<n;i++)
    G[i]=NULL;
    create(G,n);
    display(G,n);
    printf("\nEnter the starting vertex:");
    scanf("%d",&v);
    push(v);
    ct=0;
    
    while(top>=0)
    {
        vertices[ct]=pop(); 
        visited[v]=3;
        v=vertices[ct];
        ct++;
        last=G[v];
        while(last!=NULL)
        {
            if(visited[last->val]==1)
            {   push(last->val);
                visited[last->val]=2;
            }
            last=last->next;
        }
    }       
    printf("\nThe graph is:\n");
    for(i=0;i<ct;i++)
    {
        printf("\t%d",vertices[i]);
    }
}
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
void main()
{
    int graph[10][10],n,i,j,ct,v,x,vertices[10],visited[10]={1,1,1,1,1,1,1,1,1,1};
    printf("\nEnter the number of vertices of G:");
    scanf("%d",&n);
    printf("\nEnter the adjacency matrix of graph");
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            scanf("%d",&graph[i][j]);
        }

    }
    printf("\nThe adjacency matrix of given graph:\n");
    {
        for(i=0;i<n;i++)
        {
            for(j=0;j<n;j++)
            {
                printf("\t%d",graph[i][j]);
            }
            printf("\n");
        }
    }
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
        for(i=0;i<n;i++)
        {
            if(graph[v][i]==1 && visited[i]==1)
            {
                push(i);
                visited[i]=2;   
            }
        }
    }       
    printf("\nThe graph is:\n");
    for(i=0;i<ct;i++)
    {
        printf("\t%d",vertices[i]);
    }
}

#include<stdio.h>
#include<stdlib.h>

typedef struct node* nodeptr;

typedef struct node
{
    int data;
    nodeptr link;
}node;

void add(nodeptr* head,int x)
{
    nodeptr temp=malloc(sizeof(node));
    nodeptr t;

    temp->data=x;
    temp->link=NULL;

    if(!(*head))
        *head=temp;
    else
    {
        for(t=(*head);t->link;t=t->link);
        t->link=temp;
    }
}

void del(nodeptr a)
{
    nodeptr t;

    for(t=a->link;t;)
    {
        if(a->data==t->data)
        {
            a->link=t->link;
            free(t);
            t=a->link;
        }
        else
        {
            a=a->link;
            t=t->link;
        }
    }
}

void display(nodeptr a)
{
    printf("\n");

    for(;a;a=a->link)
        printf("\t%d",a->data);
}

int main()
{
    nodeptr a,b,u,in;
    int n,i,t;
    
    a=NULL;
    
    printf("\nEnter number elements of list");
    scanf("%d",&n);
    
    printf("\nEnter elements");
    for(i=0;i<n;i++)
    {
        scanf("%d",&t);
        add(&a,t);
    }
    
    display(a);
    del(a);
    display(a);
}
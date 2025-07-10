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
    nodeptr temp=(nodeptr)malloc(sizeof(node));
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

nodeptr set_union(nodeptr a,nodeptr b)
{
    int i,flag=1;
    
    nodeptr c,at,bt;
    c=NULL;
    at=a;
    bt=b;

    for(;at;at=at->link)
        add(&c,at->data);

    at=a;

    for(;bt;bt=bt->link)
    {
        for(;at;at=at->link)          
            if(bt->data==at->data)
            {
                flag=0;
                break;
            }

        if(flag)                    
            add(&c,bt->data);                       
    
        flag=1;
        at=a;
    }
    
    return c;
}

nodeptr intersection(nodeptr a,nodeptr b)
{
    nodeptr c,at;
    at=a;
    c=NULL;

    for(;b;b=b->link)
    {
        for(;at;at=at->link)
            if(b->data==at->data)
            {
                add(&c,b->data);
                break;
            }

        at=a;
    }
    
    return c;
}

void display(nodeptr a)
{
    printf("\n");

    for(;a;a=a->link)
        printf("%d --> ",a->data);

    printf("NULL\n");
}

int main()
{
    nodeptr a,b;
    int n,m,i,t;

    a=NULL;
    b=NULL;

    printf("\nEnter number elements of first set: ");
    scanf("%d",&n);

    printf("\nEnter elements: ");
    for(i=0;i<n;i++)
    {
        scanf("%d",&t);
        add(&a,t);
    }
    
    printf("\nEnter number elements of second set: ");
    scanf("%d",&m);
    
    printf("\nEnter elements: ");
    for(i=0;i<m;i++)
    {
        scanf("%d",&t);
        add(&b,t);
    }
    
    printf("\nList one: ");
    display(a);
    printf("\nList two: ");
    display(b);

    nodeptr u,in;
    
    u=set_union(a,b);
    in=intersection(a,b);
    
    printf("\nUnion: ");
    display(u);
    printf("\nIntersection: ");
    display(in);
}
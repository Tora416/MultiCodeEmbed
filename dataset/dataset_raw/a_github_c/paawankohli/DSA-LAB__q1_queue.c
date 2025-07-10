#include<stdio.h>
#include<stdlib.h>

typedef struct node* nodePointer;
typedef struct node
{
    int data;
    nodePointer link;
}node;

typedef struct
{
    nodePointer front;
    nodePointer rear;
}queue;

void init(queue* q)
{
    q->front=NULL;
    q->rear=NULL;
}

void queueFull()
{
    fprintf(stderr,"Queue Full");
    exit(EXIT_FAILURE);
}

int queueEmpty()
{
    return -1;
}

void insert(queue* q,int x)
{
    node* temp;

    if(q->front==NULL)
    {
        temp=(nodePointer)malloc(sizeof(node));
        temp->data=x;
        temp->link=NULL;
        q->front=temp;
        q->rear=temp;
    }

    else
    {
        temp=(nodePointer)malloc(sizeof(node));
        temp->data=x;
        temp->link=NULL;
        q->rear->link=temp;
        q->rear=temp;
    }
}

int deletee(queue* q)
{
    int temp;
    node* t;

    if(q->front==NULL)
        return queueEmpty();
    
    else if(q->front==q->rear)
    {
        temp=q->front->data;
        init(q);
    }
    
    else
    {
        temp=q->front->data;
        t=q->front;
        q->front=q->front->link;
        free(t);
    }
    
    return temp;
}

void display(queue* q)
{
    queue temp;
    init(&temp);
    int i;

    while(q->front!=NULL)
    {
        i=deletee(q);
        printf(" %d --> ",i);
        insert(&temp,i);
    }

    printf(" NULL\n");

    
    *q=temp;
}

int main()
{
    queue q;
    int opt ,ele;

    printf("\n1. Insert \n2. Delete \n3. Display \n4. Exit");
    
    printf("\nEnter option: ");
    scanf("%d",&opt);
    
    init(&q);
    
    while(opt!=4)
    {
        switch(opt)
        {
            case 1:
            {
                printf("\nEnter element: ");
                scanf("%d",&ele);
                insert(&q,ele);
                break;
            }
            
            case 2:
            {
                printf("\nYou have deleted %d",deletee(&q));
                break;
            }
            
            case 3:
            {
                display(&q);
                break;
            }
        }
        printf("\nEnter option: ");
        scanf("%d",&opt);
    }
    return 0;
}           
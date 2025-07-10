#include<stdio.h>
#define MAX 40
typedef enum {True=1,False=0} Ans;
typedef struct 
{
    int arr[MAX];
    int front,rear;
}QUEUE;
void init(QUEUE* q)
{
    q->front=-1;
    q->rear=-1;
}
void add(int e,QUEUE* q)
{
    if(q->rear==MAX-1)
    {
        printf("QUEUE FULL\n");
        return;
    }
    q->rear+=1;
    q->arr[q->rear]=e;
}
int del(QUEUE* q)
{
    if(q->front==q->rear)
    {
        printf("QUEUE EMPTY\n");
        return -1;
    }
    q->front+=1;
    return q->arr[q->front];
}
Ans find(QUEUE* q,int e)
{
    QUEUE q1;
    QUEUE* nq=&q1;
    int num;
    Ans f=False;
    init(nq);
    while(q->front!=q->rear)
    {
        num=del(q);
        if(num==e)
        {
            f=True;
            add(num,nq);
        }
        else
            add(num,nq);
    }
    while(nq->front!=nq->rear)
    {
        add(del(nq),q);
    }
    return f;
}
void display(QUEUE* q)
{
    int i;
    for(i=q->front+1;i<=q->rear;i=i+1)
        printf("%d\t",q->arr[i]);
    printf("\n");
}
int main()
{
    QUEUE q;
    QUEUE* q1=&q;
    init(q1);
    add(1,q1);
    add(2,q1);
    add(3,q1);
    add(4,q1);
    add(5,q1);
    add(6,q1);
    add(7,q1);
    if(find(q1,9))
        printf("Found\n");
    else
        printf("Not Found\n");
    if(find(q1,5))
        printf("Found\n");
    else
        printf("Not Found\n");
    display(q1);
}
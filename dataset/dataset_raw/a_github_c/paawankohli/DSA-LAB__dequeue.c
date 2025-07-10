#include <stdio.h>
typedef struct
{
    int c[20];
    int front;
    int rear;
}queue;
void enqueueright(queue *q,int n)
{
    if (q->rear==20)
        printf("Side Full\n");
    else
        q->c[(q->rear)++]=n;
}
void enqueueleft(queue *q,int n)
{
    if (q->front==0)
        printf("Side Full\n");
    else
        q->c[--(q->front)]=n;
}
int dequeueleft(queue *q)
{
    if (q->front==q->rear)
    {
        printf("Queue Empty");
        return -1;
    }
    else
        return q->c[(q->front)++];
}
int dequeueright(queue *q)
{
    if (q->front==q->rear)
    {
        printf("Queue Empty");
        return -1;
    }
    else
        return q->c[--(q->rear)];
}
void display(queue *q)
{
    int i;
    for (i=q->front;i<q->rear;i++)
        printf("%d\t",q->c[i]);
    printf("\n");
}
int main()
{
    int z=0,k,e;
    queue q;
    q.front=10;
    q.rear=10;
    while (z==0)
    {
        printf("1. Enqueue Right\t2. Enqueue Left\t3. Dequeue Left\t4. Dequeue Right\t5. Display \t6. Exit\n");
        scanf("%d",&k);
        switch(k)
        {
            case 1:
            {
                scanf("%d",&e);
                enqueueright(&q,e);
                break;
            }
            case 2:
            {
                scanf("%d",&e);
                enqueueleft(&q,e);
                break;
            }
            case 3:
            {
                printf ("%d\n",dequeueleft(&q));
                break;
            }
            case 4:
            {
                printf ("%d\n",dequeueright(&q));
                break;
            }
            case 5:
            {
                display(&q);
                break;
            }
            case 6:
            {
                z=1;
            }
        }
    }
}
#include <stdio.h>
typedef struct
{
    int c[20];
    int front;
    int rear;
}queue;
void enqueue(queue *q,int n)
{
    if (q->rear==20)
        printf("Queue Full\n");
    else
    {
        int i,j,t;
        q->c[(q->rear)++]=n;
        for (i=0;i<q->rear-1;i++)
        {
            for (j=0;j<q->rear-i-1;j++)
            {
                if (q->c[j]>q->c[j+1])
                {
                    t=q->c[j];
                    q->c[j]=q->c[j+1];
                    q->c[j+1]=t;
                }
            }
        }
    }
}
int dequeue(queue *q)
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
    q.front=0;
    q.rear=0;
    while (z==0)
    {
        printf("1. Enqueue \t4. Dequeue \t5. Display \t6. Exit\n");
        scanf("%d",&k);
        switch(k)
        {
            case 1:
            {
                scanf("%d",&e);
                enqueue(&q,e);
                break;
            }
            case 2:
            {
                break;
            }
            case 3:
            {
                break;
            }
            case 4:
            {
                printf ("%d\n",dequeue(&q));
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
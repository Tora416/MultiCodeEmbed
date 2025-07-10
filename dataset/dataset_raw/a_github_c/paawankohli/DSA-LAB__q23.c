#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    char *c[20];
    int front;
    int rear;
}queue;

void enqueueright(queue *q,char* n)
{
    if (q->rear == 20)
        printf("Side Full\n");
    else
        q->c[(q->rear)++]=n;
}

void enqueueleft(queue *q,char* n)
{
    if (q->front == 0)
        printf("Side Full\n");
    else
        q->c[--(q->front)]=n;
}

void dequeueleft(queue *q)
{
    if (q->front==q->rear)
        printf("Queue Empty");

    else
        printf("\n%s deleted", q->c[(q->front)++] );

}

void dequeueright(queue *q)
{
    if (q->front==q->rear)
        printf("Queue Empty");
    
    else
        printf("\n%s deleted", q->c[--(q->rear)] );
}

void display(queue *q)
{
    int i;

    for (i = q->front ; i<q->rear ; i++)
        printf("%s\t",q->c[i]);
    
    printf("\n");
}

int main()
{
    int z=0,k,e;
    queue q;

    q.front=10;
    q.rear=10;

    printf("1. Enqueue Right\n2. Enqueue Left\n3. Dequeue Left\n4. Dequeue Right\n5. Display \n6. Exit\n");
    
    while (z == 0)
    {
        printf("\nCommand: ");
        scanf("%d",&k);
        switch(k)
        {
            case 1:
            {
                printf("\nEnter String: ");
                char *n = malloc(30);
                scanf("%s", n);

                enqueueright(&q,n);
                break;
            }
            
            case 2:
            {
                printf("\nEnter String: ");
                char *n = malloc(30);
                scanf("%s", n);

                enqueueleft(&q,n);
                break;
            }
            
            case 3:
            {
                dequeueleft(&q);
                break;
            }
            
            case 4:
            {
                
                printf ("\n:::::::::OPERATION NOT ALLOWED:::::::\n");

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
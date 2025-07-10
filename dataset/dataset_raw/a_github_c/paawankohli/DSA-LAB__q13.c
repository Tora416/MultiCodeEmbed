#include <stdio.h>
#include <stdlib.h>
#define size 5

typedef struct
{
    char* queue[size];
    int front;
    int rear;

}que;

void insertq(que* pq, char* item)
{
    if ((pq->front == 0 && pq->rear == size - 1) || (pq->front == pq->rear + 1))
    {
        printf("queue is full");
        return;
    }

    else if (pq->rear ==  -1)
    {
        pq->rear++;
        pq->front++;
    }

    else if (pq->rear == size - 1 && pq->front > 0)
    {
        pq->rear = 0;
    }

    else
    {
        pq->rear++;
    }

    pq->queue[pq->rear] = item;
}

void display(que* pq)
{
    int i;
    printf("\n");

    if (pq->front ==  -1)
    {
        printf("Queue is empty");
        return;
    }

    if (pq->front > pq->rear)
    {
        for (i = pq->front; i < size; i++)
            printf("%s\n", pq->queue[i]);
        
        for (i = 0; i <= pq->rear; i++)
            printf("%s\n", pq->queue[i]);
    }

    else
    {
        for (i = pq->front; i <= pq->rear; i++)
            printf("%s\n", pq->queue[i]);
    }
}

void deleteq(que* pq)
{
    if (pq->front ==  -1)
        printf("Queue is empty");
    
    else if (pq->front == pq->rear)
    {
        printf("\n%s deleted", pq->queue[pq->front]);
        pq->front =  -1;
        pq->rear =  -1;
    }

    else if (pq->front == size - 1) 
    {
        printf("\n%s deleted", pq->queue[pq->front]);
        pq->front = 0;
    }
    
    else
        printf("\n%s deleted", pq->queue[(pq->front)++]);

}

int main()
{
    int ch;
    que q;

    q.front = q.rear = -1;

    do
    {
        printf("\nCircular Queue:\n1. Insert \n2. Delete\n3. Display\n0. Exit");
        printf("\nEnter Choice 0-3? : ");
        scanf("%d", &ch);

        switch (ch)
        {
            case 1:
                printf("\nEnter String: ");
                
                char *n = malloc(30);
                scanf("%s", n);

                insertq(&q, n);
                break;

            case 2:
                deleteq(&q);
                break;

            case 3:
                display(&q);
                break;
        }

    }while (ch != 0);
}
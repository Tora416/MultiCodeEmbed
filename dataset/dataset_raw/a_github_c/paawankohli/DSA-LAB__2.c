#include <stdio.h>
#define MAX 100

typedef struct
{
    int q[100];
    int front;
    int rear;
}QUEUE;

int isEmpty(QUEUE* pq)
{
    if (pq->front == pq->rear)
        return 1;
    else
        return 0;
}

int isFull(QUEUE* pq)
{
    if (pq->rear == MAX - 1)
        return 1;
    else
        return 0;
}

void enqueue(QUEUE* pq, int x)
{
    if(isFull(pq) == 0)
        pq->q[(pq->rear)++] = x;
    else
        printf("FULL");
}

int dequeue(QUEUE* pq)
{
    if (isEmpty(pq) == 1)
        return -1;
    else
        return pq->q[(pq->front)++];
}

void display(QUEUE* pq)
{
    for(int i = pq->front ; i < pq->rear ; i++)
        printf("%d ", pq->q[i]);

    printf("\n");

}

void reverse(QUEUE* q1, QUEUE* q2, int n)                                   
{
    if(n == 0)
        return;

    int x = dequeue(q1);
    reverse(q1, q2, n - 1);
    enqueue(q2, x);
}

int main()
{
    QUEUE q1, q2; q1.front = q1.rear = q2.front = q2.rear = 0;            

    int n;
    printf("Enter no. of elements: ");
    scanf("%d", &n);
    
    printf("Enter elements: ");

    for(int i = 0 ; i < n ; i++)
    {
        int a;
        scanf("%d", &a);
        enqueue(&q1, a);
    }


    

    printf("QUEUE 1:");    display(&q1);
    
    reverse(&q1, &q2,n);

    

    printf("QUEUE 2:");    display(&q2);
    
    return 0;
}




















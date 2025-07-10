#include <stdio.h>
#include<string.h>
#define CAPACITY 100

typedef struct
{
    char c[CAPACITY];
    int front;
    int rear;
}queue;

void enqueueright(queue *q,char n)
{
    if (q->rear == CAPACITY)
        printf("Side Full\n");
    
    else
        q->c[(q->rear)++]=n;
}

void enqueueleft(queue *q,char n)
{
    if (q->front==0)
        printf("Side Full\n");
    
    else
        q->c[--(q->front)]=n;
}

char dequeueleft(queue *q)
{
    if (q->front==q->rear)
    {
        printf("Queue Empty");
        return '\0';
    }
    
    else
        return q->c[(q->front)++];
}

char dequeueright(queue *q)
{
    if (q->front==q->rear)
    {
        printf("Queue Empty");
        return '\0';
    }
    
    else
        return q->c[--(q->rear)];
}

void display(queue *q)
{
    int i;

    for (i=q->front;i<q->rear;i++)
        printf("%c ",q->c[i]);
    
    printf("\n");
}

int getSize(queue *q)
{
    return q->rear - q->front;
}

int main()
{
    queue q;
    q.front = CAPACITY/2;
    q.rear = CAPACITY/2;

    char word[20];
    int isPalin  = 1;          

    printf("Enter word: ");
    scanf("%s", word);

    for(int i = 0 ; i < strlen(word) ; i++)
        enqueueright(&q, word[i]);


    for(int i = 0 ; i < strlen(word)/2 ; i++)
        if (dequeueleft(&q) != dequeueright(&q))
        {
            isPalin = 0;              
            break;
        }

    isPalin ? printf("YES\n") : printf("NO\n");
}
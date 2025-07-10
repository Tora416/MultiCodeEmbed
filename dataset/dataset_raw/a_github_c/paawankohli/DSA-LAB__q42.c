#include<stdio.h>
#define MAX 40

typedef struct 
{
    int stack1[MAX];
    int stack2[MAX];
    int top1,top2;
}QUEUE;

void add(QUEUE* q, int ele)
{
    if(q->top1 == MAX)
    {
        printf("QUEUE FULL \n");
        return;
    }
    
    q->top1++;
    q->stack1[q->top1] = ele;
}

int del(QUEUE* q)
{
    if(q->top1 == -1 && q->top2 == -1)
    {
        printf("QUEUE EMPTY\n");
        return -1;
    }

    if(q->top2 == -1)
        while(q->top1 != -1)
            q->stack2[++(q->top2)] = q->stack1[(q->top1)--];
        
    return q->stack2[(q->top2)--];
}

int main()
{
    QUEUE q;

    q.top1 = -1;
    q.top2 = -1;

    int ch, n;

    do
    {
        printf("\n\n1. Insert\n2. Delete\n0. Exit");
        printf("\nEnter Choice? : ");
        scanf("%d", &ch);

        switch (ch)
        {
            case 1:
                printf("\nEnter number: ");
                scanf("%d", &n);
                add(&q, n);
                break;

            case 2:
                printf("\n%d deleted \n", del(&q));
                break;
        }

    }while (ch != 0);
    
    return 0;
}
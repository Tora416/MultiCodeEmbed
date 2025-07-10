

#include <stdio.h>
#include <stdlib.h>
#define n 5
int queue[n];
int front=-1;
int rear=-1;
void enqueue(int x)
{
    if(rear==n-1)
    {
        printf("overflow\n");
    }
    else if(front==-1 && rear==-1)
    {
        front=rear=0;
        printf("the inserted element is %d\n",x);
        queue[rear]=x;
    }
    else
    {
        rear++;
        printf("the inserted element is %d\n",x);
        queue[rear]=x;
    }
}
void dequeue()
{
    if(front==-1 && rear==-1)
    {
        printf("underflow\n");
    }
    else if(front==rear)
    {
        printf("the delete element is %d\n",queue[front]);
        front=rear=-1;
    }
    else
    {
        printf("the delete element is %d\n",queue[front]);
        front++;
    }
}
void peek()
{
    if(front==-1 && rear==-1)
    {
        printf("queue is empty\n");
    }
    else
    {
        printf("the peek element is %d\n",queue[front]);
    }
}
void display()
{
    int i;
    if(front==-1 && rear==-1)
    {
        printf("queue is empty\n");
    }
    else
    {
        printf("the elements in the queue are\n");
        for(i=front;i<=rear;i++)
        {
            printf("%d ",queue[i]);
        }
        printf("\n");
    }
}
int main()
{
    printf("the queue using array\n");
    enqueue(4);
    enqueue(10);
    enqueue(41);
    display();
    dequeue();
    peek();
    enqueue(25);
    dequeue();
    peek();
    display();
}


#include<stdio.h>
#include<stdlib.h>
#define MAX 100
int queue[MAX];
int value,front=-1,rear=-1;
void enqueue(int queue[],int val)
{
    if(rear==MAX-1)
    printf("\nqueue is full");
    if(front==-1 && rear==-1)
    {
        front=0;
        rear=rear+1;
        queue[rear]=val;
    }
    else
    {
        rear=rear+1;
        queue[rear]=val;
    }
}
void dequeue(int queue[])
{
    if(front==-1 || front>rear)
    {
        printf("\nqueue is empty");
    }
    else
    {
        printf("\nThe value popped is : %d",queue[front]);
        front=front+1;
    }
}
void search(int queue[],int val)
{
    int i,c=0;
    if(front==-1 || front>rear)
    printf("\nqueue is empty");
    else
    {
        for(i=front;i<=rear;i++)
        {
            if(queue[i]==val)
            {
                printf("\nvalue found");
                c=c+1;
                break;
            }
        }
        if(c==0)
        printf("\nvalue not found");
    }
}
void display(int stack[])
{
    int i;
    if(front==-1 || front>rear)
    printf("\nqueue is empty");
    else
    {
        printf("\nqueue is :\n");
        for(i=front;i<=rear;i++)
        printf("\t%d",queue[i]);
    }
}
void main()
{
    int ch;
    printf("1.ENQUEUE\n2.DEQUEUE\n3.SEARCH\n4.PRINT\n\n");
    while(1)
    {
        printf("\nEnter choice:");
        scanf("%d",&ch);
        switch(ch)
        {
            case 1:
            {
                printf("\nEnter the value to insert:");
                scanf("%d",&value);
                enqueue(queue,value);
                break;
            }
            case 2:
            {
                dequeue(queue);
                break;
            }
            case 3:
            {
                printf("\nEnter the value to search:");
                scanf("%d",&value);
                search(queue,value);
                break;
            }
            case 4:
            {
                display(queue);
                break;
            }
            default:
            {
                exit(0);
                break;
            }
        }
    }
}
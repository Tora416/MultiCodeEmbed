
#include<stdio.h>
#include<stdlib.h>
#define MAX 100
int queue[MAX];
int value,front=-1,rear=-1;
void enqueueF(int val)
{
    if(front==-1 && rear==-1)
    {
        front=front+1;
        rear=rear+1;
        queue[front]=val;
    }
    else if(front==0)
    {
        printf("\ncannot be inserted");
    }
    else
    {
        front=front-1;
        queue[front]=val;
    }
}
void enqueueR(int val)
{
    if(front==-1 && rear==-1)
    {
        front=front+1;
        rear=rear+1;
        queue[rear]=val;
    }
    if(rear==MAX-1)
    printf("queue is full");
    else
    {
        rear=rear+1;
        queue[rear]=val;
    }
}
void dequeueF()
{
    if((front==-1 && rear==-1) || front>rear)
    printf("queue is empty");
    else
    {
        printf("The value popped is %d",queue[front]);
        front=front+1;
    }
}
void dequeueR()
{
    if((front==-1 && rear==-1) || front>rear)
    printf("queue is empty");
    else
    {
        printf("The value popped is %d",queue[rear]);
        rear=rear-1;
    }
}
void search(int val)
{
    int i,c=0;
    if((front==-1 && rear==-1) || front>rear)
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
void display()
{
    int i;
    if((front==-1 && rear==-1) || front>rear)
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
    printf("1.enqueueF\n2.enqueueR\n3.dequeueF\n4.dequeueR\n5.search\n6.print\n\n");
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
                enqueueF(value);
                break;
            }
            case 2:
            {
                printf("\nEnter the value to insert:");
                scanf("%d",&value);
                enqueueR(value);
                break;
            }
            case 3:
            {
                dequeueF();
                break;
            }
            case 4:
            {
                dequeueR();
                break;
            }
            case 5:
            {
                printf("\nEnter the value to search:");
                scanf("%d",&value);
                search(value);
                break;
            }
            case 6:
            {
                display();
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
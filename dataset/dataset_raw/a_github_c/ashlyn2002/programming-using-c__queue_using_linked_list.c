

#include <stdio.h>
#include <stdlib.h>
struct node
{
    int data;
    struct node *next;
};
struct node *front=0;
struct node *rear=0;
void enqueue(int x)
{
    struct node *newnode;
    newnode=(struct node*)malloc(sizeof(struct node));
    newnode->data=x;
    newnode->next=0;
    printf("the data inserted is %d\n",x);
    if(front==0 && rear==0)
    {
        front=rear=newnode;
    }
    else
    {
       rear->next=newnode;
       rear=newnode;
    }
}
void peek()
{
    if(front==0 && rear==0)
    {
        printf("the queue is empty\n");
    }
    else
    {
        printf("the peek element is %d \n",front->data);
    }
}
void dequeue()
{
    struct node *temp;
    temp=front;
    if(front==0 && rear==0)
    {
        printf("the queue is empty\n");
    }
    else if(front==rear)
    {
        printf("the delete element is %d \n",temp->data);
        front=rear=0;
        free(temp);
    }
    else
    {
        printf("the delete element is %d \n",temp->data);
        front=front->next;
        free(temp);
    }
}
void display()
{
    struct node *temp;
    temp=front;
    if(front==0 && rear==0)
    {
        printf("the queue is empty\n");
    }
    else
    {
        printf("the element in the array are\n");
       while(temp!=0)
       {
           printf("%d ",temp->data);
           temp=temp->next;
       }printf("\n");
    }
}
int main()
{
    printf("queue using the linked list\n");
    enqueue(17);
    enqueue(34);
    enqueue(55);
    dequeue();
    enqueue(20);
    display();
    peek();
    dequeue();
    enqueue(45);
    peek();
    display();
}

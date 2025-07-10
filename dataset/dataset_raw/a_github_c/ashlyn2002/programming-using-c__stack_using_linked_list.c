

#include <stdio.h>
#include <stdlib.h>
struct node
{
    int data;
    struct node *next;
};
struct node *top=0;
void push(int x)
{
    struct node *newnode;
    newnode=(struct node*)malloc(sizeof(struct node));
    newnode->data=x;
    newnode->next=top;
    top=newnode;
    printf("the element pushed into the stack is %d\n",x);
}
void display()
{
    struct node *temp;
    temp=top;
    if(top==0)
    {
        printf("the stack is empty\n");
    }
    else
    {
        printf("the elements in the stack are\n");
        while(temp!=0)
        {
            printf("%d ",temp->data);
            temp=temp->next;
        }
        printf("\n");
    }
}
void peek()
{
    if(top==0)
    {
        printf("the stack is empty\n");
    }
    else
    {
        printf("the peek element is %d\n",top->data);
    }
}
void pop()
{
    struct node *temp;
    if(top==0)
    {
        printf("the stack is under flow\n");
    }
    else
    {
        temp=top;
        printf("the poped element is %d\n",top->data);
        top=top->next;
        free(temp);
    }
}
int main()
{
    printf("the stack using linked list\n");
    push(2);
    push(3);
    push(10);
    display();
    peek();
    pop();
    peek();
    display();
}

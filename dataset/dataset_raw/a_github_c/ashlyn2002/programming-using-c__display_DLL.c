

#include <stdio.h>
#include <stdlib.h>

void creat();
void display();
struct node
{
    int data;
    struct node *next;
    struct node *pre;
};
struct node *head=0;
int main()
{
    printf("function of double linked list \n");
    printf("1.implementation\n");
    creat();
    printf("2.display the linked list\n");
    display();
}
void creat()
{
    struct node *newnode,*temp;
    int choice;
    while(choice)
    {
        newnode=(struct node *)malloc(sizeof(struct node));
            printf("enter the data =");
            scanf("%d",&newnode->data);
            newnode->pre=0;
            newnode->next=0;
        if(head==0)
        {
            head=temp=newnode;
        }
        else
        {
            temp->next=newnode;
            newnode->pre=temp;
            temp=newnode;
        }
        printf("do you need to continue(0,1)?\n enter 0 to stop  enter 1 to continue = ");
        scanf("%d",&choice);
    }
}
void display()
{
    struct node *temp;
    temp=head;
    while(temp!=0)
    {
        printf("%d ",temp->data);
        temp=temp->next;
    }
}


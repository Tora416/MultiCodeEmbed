

#include <stdio.h>
#include <stdlib.h>

void create();
struct node
{
    int data;
    struct node *next;
    struct node *pre;
};
struct node *head=0;
int main()
{
    printf("function of doubly circular linked list \n");
    printf("1.implementation \n");
    create();
}
void create()
{
    struct node *newnode,*temp;
    int choice;
    while(choice)
    {
        newnode=(struct node*)malloc(sizeof(struct node));
        printf("enter the data =");
        scanf("%d",&newnode->data);
        newnode->pre=0;
        newnode->next=0;
        if(head==0)
        {
            head=temp=newnode;
            newnode->next=newnode;
            newnode->pre=newnode;
        }
        else
        {
            temp->next=newnode;
            newnode->pre=temp;
            newnode->next=head;
            temp=newnode;
            head->pre=temp;
        }
    printf("do you need to continue(0,1)?\nenter 0 to stop and 1 to continue =");
    scanf("%d",&choice);
    }

}

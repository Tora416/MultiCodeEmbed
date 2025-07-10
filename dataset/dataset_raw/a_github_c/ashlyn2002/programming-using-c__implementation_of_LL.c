

#include <stdio.h>
#include <stdlib.h>
void create();
struct node
    {
        int data;
        struct node *next;
    };
    struct node *head=0;
    int main()
{
    printf("Linked list functions\n");
    printf("implementation\n");
    create();
}
void create()
{
    struct node *newnode,*temp;
    int choice;
    while(choice)
    {
        newnode=(struct node*)malloc(sizeof(struct node));
            printf("enter the data = ");
            scanf("%d",& newnode->data);
            newnode->next=0;
       if(head==0)
       {
            head=temp=newnode;
       }
       else
       {
            temp->next=newnode;
            temp=newnode;
       }
       printf("do you need to continue (0,1)?\n0 to stop 1 to continue the element in the linked list =");
       scanf("%d",& choice);
    }
}

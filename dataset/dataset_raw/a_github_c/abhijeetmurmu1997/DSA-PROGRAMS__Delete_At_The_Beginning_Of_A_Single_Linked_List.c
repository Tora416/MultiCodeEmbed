#include<stdlib.h>
#include<conio.h>
#include<stdio.h>
void display_node();
void delete_at_start();
struct node
{
    int data;
    struct node*ptr;
};
int main()
{
    int choice = 1;
    struct node*head,*temp;
    head = temp = NULL;
    struct node*newnode;
    while(choice!=0)
    {
        newnode = (struct node*) malloc (sizeof(struct node));
        printf("Enter the data:");
        scanf("%d",&newnode->data);
        newnode->ptr = NULL;
        
        if(head == NULL)
        {
            head = temp = newnode;
        }
        else
        {
            temp->ptr = newnode;
            temp = newnode;
        }
        printf("Do you want to enter more nodes?(1/0)");
        scanf("%d",&choice);
    }
    temp = head;
    display_node(temp);
    delete_at_start(head,temp);
    getch();
}
void display_node(struct node*temp1)
{
    printf("The Elements are:");
    while(temp1!=NULL)
    {
        printf("%d\t",temp1->data);
        temp1 = temp1->ptr;
    }
}
void delete_at_start(struct node*head1, struct node*temp1)
{
    head1 = head1->ptr;
    free(temp1);
    printf("\nAfter Deletion:");
    while(head1!=NULL)
    {
        printf("%d\t",head1->data);
        head1 = head1->ptr;
    }
}

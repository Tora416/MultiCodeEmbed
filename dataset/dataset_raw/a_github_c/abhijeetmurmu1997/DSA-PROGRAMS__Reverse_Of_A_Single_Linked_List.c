#include<stdio.h>
#include<stdlib.h>
void display_node();
void reverse_node();
struct node
{
    int data;
    struct node*ptr;
};
int main()
{
    int choice;
    printf("PRESS 1 FOR CREATION OR ELSE PRESS 0 FOR TERMINATION:");
    scanf("%d",&choice);
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
        printf("DO YOU WANT TO ENTER MORE?(1/0)");
        scanf("%d",&choice);
    }
    temp = head;
    display_node(temp);
    reverse_node(head,temp);
    getch();    
}
void display_node(struct node*temp1)
{
    printf("THE ELEMENTS ARE:");
    while(temp1!=NULL)
    {
        printf("%d\t",temp1->data);
        temp1 = temp1->ptr;
    }
}
void reverse_node(struct node*head1, struct node*temp1)
{
    struct node*prevnode;
    if(head1!=NULL)
    {
        prevnode = head1;
        temp1 = head1->ptr;
        head1 = head1->ptr;
        prevnode->ptr = NULL;
    }
    while(head1!=NULL)
    {
        head1 = head1->ptr;
        temp1->ptr = prevnode;
        prevnode = temp1;
        temp1 = head1;
    }
    head1 = prevnode;
    printf("\nAFTER REVERSE OPERATION:");
    while(head1!=NULL)
    {
        printf("%d\t",head1->data);
        head1 = head1->ptr;
    }
    return;
}

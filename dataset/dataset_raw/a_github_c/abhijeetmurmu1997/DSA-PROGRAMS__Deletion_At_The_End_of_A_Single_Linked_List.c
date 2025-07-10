#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
void display_nodes();
void delete_at_end();
struct node
{
    int data;
    struct node*ptr;
};
int main()
{
    int choice;
    printf("Enter 1 for Creation or Enter 0 for Termination:");
    scanf("%d",&choice);
    struct node*head,*temp;
    head = temp = NULL;
    struct node*newnode;
    while(choice!=0)
    {
        newnode = (struct node*) malloc (sizeof(struct node));
        printf("Enter the Data:");
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
        printf("Do you want to more?(1/0)");
        scanf("%d",&choice);
    }
    temp = head;
    display_nodes(temp);
    delete_at_end(head,temp);
    getch();
}
void display_nodes(struct node*temp1)
{
    printf("The Elements are:");
    while(temp1!=NULL)
    {
        printf("%d\t",temp1->data);
        temp1 = temp1->ptr;
    }
}
void delete_at_end(struct node*head1, struct node*temp1)
{
    struct node*prevnode;
    while(temp1->ptr!=NULL)
    {
        prevnode = temp1;
        temp1 = temp1->ptr;
    }
    prevnode->ptr = NULL;
    free(temp1);
    prevnode = head1;
    printf("\nAfter Deletion:");
    while(prevnode!=NULL)
    {
        printf("%d\t",prevnode->data);
        prevnode = prevnode->ptr;
    }
}

#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
void display_node();
void insert_at_begin();
struct node
{
    int data;
    struct node*ptr;
};
int main()
{
    int choice;
    printf("Enter 1 for Creation or 0 for Termination:");
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
        printf("DO you want to enter more?(1/0)");
        scanf("%d",&choice);
    }
    temp = head;
    display_node(temp);
    insert_at_begin(head,temp);
    getch();    
}
void display_node(struct node*temp1)
{
    printf("The elements are:");
    while(temp1!=NULL)
    {
        printf("%d\t",temp1->data);
        temp1 = temp1->ptr;
    }
}
void insert_at_begin(struct node*head1,struct node*temp1)
{
    struct node*tempo;
    tempo = (struct node*) malloc (sizeof(struct node));
    printf("\nEnter the data:\n");
    scanf("%d",&tempo->data);
    tempo->ptr = temp1;
    head1 = temp1 = tempo;
    printf("After Insertion:");
    while(temp1!=NULL)
    {
        printf("%d\t",temp1->data);
        temp1 = temp1->ptr;
    }
}

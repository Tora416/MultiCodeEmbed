#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
void display_node();
void insert_at_N_position();
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
        printf("Do you want to enter more?(1/0)");
        scanf("%d",&choice);
    }
    temp = head;
    display_node(temp);
    insert_at_N_position(head,temp);
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
void insert_at_N_position(struct node*head1, struct node*temp1)
{
    int pos,i;
    printf("\nAt what position you want to insert?\n");
    scanf("%d",&pos);
    struct node*tempo;
    tempo = (struct node*) malloc (sizeof(struct node));
    printf("Enter the data:");
    scanf("%d",&tempo->data);
    if(pos == 0)
    {
        printf("After Insertion, the List is:\n");
        while(temp1!=NULL)
        {
            printf("%d\t",temp1->data);
            temp1 = temp1->ptr;
        }
        printf("\nSORRY!!! NO ADDITIONAL NODE IS INSERTED :(");
        return;
    }
    if(pos == 1)
    {
        tempo->ptr = temp1;
        head1 = temp1 = tempo;
        printf("After Insertion, The List is:\n");
        while(temp1!=NULL)
        {
            printf("%d\t",temp1->data);
            temp1 = temp1->ptr;
        }
        return;
    }
    for(i=1;i<pos-1;i++)
    {
        temp1 = temp1->ptr;
    }
    tempo->ptr = temp1->ptr;
    temp1->ptr = tempo;
    temp1 = head1;
    printf("After Insertion, The List is:\n");
    while(temp1!=NULL)
    {
        printf("%d\t",temp1->data);
        temp1 = temp1->ptr;
    }
}

#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
void display_node();
struct node
{
    int data;
    struct node*link;
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
        newnode->link = NULL;
        
        if(head == NULL)
        {
            head = temp = newnode;
        }
        else
        {
            temp->link = newnode;
            temp = newnode;
        }
        printf("Do you want to enter more node?(1/0)");
        scanf("%d",&choice);
    }
    temp = head;
    display_node(temp);
    getch();
}
void display_node(struct node*temp1)
{
    printf("The Elements are:");
    while(temp1!=NULL)
    {
        printf("%d\t",temp1->data);
        temp1 = temp1->link;
    }
}

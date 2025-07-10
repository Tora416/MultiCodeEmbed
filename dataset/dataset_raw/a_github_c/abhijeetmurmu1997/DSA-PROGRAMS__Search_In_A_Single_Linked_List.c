#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
void display_node();
void search_node();
struct node
{
    int data;
    struct node*link;
};
int main()
{
    int choice;
    printf("ENTER 1 FOR CREATION ELSE ENTER 0 FOR TERMINATION:");
    scanf("%d",&choice);
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
        printf("DO YOU WANT TO ENTER MORE?(1/0)");
        scanf("%d",&choice);
    }
    temp = head;
    display_node(temp);
    search_node(head,temp);
    getch();
}
void display_node(struct node*temp1)
{
    printf("THE ELEMENTS ARE:");
    while(temp1!=NULL)
    {
        printf("%d\t",temp1->data);
        temp1 = temp1->link;
    }
}
void search_node(struct node*head1, struct node*temp1)
{
    int val;
    printf("\nWHICH ELEMENT YOU ARE LOOKING FROM THE ABOVE LIST?\n");
    scanf("%d",&val);
    int count = 1;
    while(temp1->data!=val)
    {
        count++;
        temp1 = temp1->link;
    }
    printf("THE ELEMENT %d IS PRESENT AT POSITION %d",temp1->data,count);
    return;
}

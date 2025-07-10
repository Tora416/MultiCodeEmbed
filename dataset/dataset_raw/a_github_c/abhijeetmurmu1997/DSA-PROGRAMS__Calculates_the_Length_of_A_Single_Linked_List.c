#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
void display_nodes();
int length();
struct node
{
    int data;
    struct node*ptr;
};
int main()
{
    int choice;
    printf("Press 1 for Creation or else Press 0 for Termination:");
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
        printf("Do you want ot enter more?(1/0)");
        scanf("%d",&choice);
    }
    temp = head;
    display_nodes(temp);
    length(temp);
    getch();
}
void display_nodes(struct node*temp1)
{
    printf("The elements are:");
    if(temp1 == 0)
    {
        printf("NO DATA");
    }
    else
    while(temp1!=NULL)
    {
        printf("%d\t",temp1->data);
        temp1 = temp1->ptr;
    }
}
int length(struct node*temp2)
{
    int count = 0;
    printf("\nThe Length Of The Linked List is:");
    while(temp2!=NULL)
    {
        count++;
        temp2 = temp2->ptr;
    }
    printf("%d",count);
}


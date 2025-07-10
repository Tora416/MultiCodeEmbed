#include<stdio.h>
#include<stdlib.h>
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
    while(choice)
    {
        newnode = (struct node*) malloc(sizeof(struct node));
        printf("Enter the element in the node:");
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
        printf("Do you want to enter more nodes?(0/1)");
        scanf("%d",&choice);
    }
    temp = head;
    int count = 0;
    printf("THE ELEMENTS PRESENT IN THE NODE ARE\n");
    while(temp!=NULL)
    {
        count++;
        printf("%d\t",temp->data);
        temp = temp->link;
    }
    printf("\nCount : %d",count);
    return 0;
}

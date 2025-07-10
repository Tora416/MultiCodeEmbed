#include<stdio.h>
#include<stdlib.h>
struct node
{
    int data;
    struct node*link;
};
int insert_at_end(struct node*temp1)
{
    struct node*tempo;
    tempo = (struct node*) malloc (sizeof(struct node));
    printf("Enter the data:");
    scanf("%d",&tempo->data);
    tempo->link = NULL;
    temp1->link = tempo;
}
int main()
{
    int choice = 1;
    struct node*head,*temp;
    head = NULL;
    struct node*newnode;
    while(choice)
    {
        newnode = (struct node*) malloc (sizeof(struct node));
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
        printf("DO YOU WANT TO ENTER MORE NODES?(0/1)");
        scanf("%d",&choice);
    }
    insert_at_end(temp);
    temp = head;
    int count = 0;
    printf("THE ENTERED ELEMENTS IN THE NODE ARE\n");
    while(temp!=NULL)
    {
        count++;
        printf("%d\t",temp->data);
        temp = temp->link; 
    }
    printf("\nCount : %d",count);
    return 0;
}


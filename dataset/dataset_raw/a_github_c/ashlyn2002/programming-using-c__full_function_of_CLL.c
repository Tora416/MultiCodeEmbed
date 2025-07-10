

#include <stdio.h>
#include <stdlib.h>

void create();
void display();
int count();
void insert_beg();
void insert_end();
void insert_at_pos();
void delete_beg();
void delete_end();
void delete_at_pos();
struct node
{
    int data;
    struct node *next;
};
struct node *head=0;
int main()
{
    int choice;
    printf("the function of circular linked list\n");
    printf("1.implementation of linked list\n");
    printf("2.display the linked list\n");
    printf("3.count the number of elements in the linked list\n");
    printf("4.insert the element at the beginning position \n");
    printf("5.insert the element at the last position \n");
    printf("6.insert the element at any position \n");
    printf("7.delete the element from the beginning position\n");
    printf("8.delete the element from the last position\n");
    printf("9.delete the element from any position\n");
    printf("10.exit\n");
    printf("enter your choice =");
    scanf("%d",&choice);
    while(choice!=11)
    {
        switch(choice)
        {
            case 1:printf("implementation of linked list\n");
            create();
            break;
            case 2:printf("display the linked list\n");
            display();
            break;
            case 3:printf("count the number of elements in the linked list\n");
            count();
            break;
            case 4:printf("insert the element at the beginning position \n");
            insert_beg();
            break;
            case 5:printf("insert the element at the last position \n");
            insert_end();
            break;
            case 6:printf("insert the element at any position \n");
            insert_at_pos();
            break;
            case 7:printf("delete the element from the beginning position\n");
            delete_beg();
            break;
            case 8:printf("delete the element from the last position\n");
            delete_end();
            break;
            case 9:printf("delete the element from any position\n");
            delete_at_pos();
            break;
            case 10:printf("exit\n");
            exit(0);
            break;
            default:printf("wrong choice \n");
            break;
        }
        printf("enter your choice =");
        scanf("%d",&choice);
    }
}
void create()
{
    struct node *newnode,*temp;
    int choice;
    while(choice)
    {
        newnode=(struct node *)malloc(sizeof(struct node));
        printf("enter the data =");
        scanf("%d",&newnode->data);
        newnode->next=0;
        if(head==0)
        {
            head=temp=newnode;
        }
        else
        {
            temp->next=newnode;
            temp=newnode;
        }
        temp->next=head;
        printf("do you need to continue(0,1)?\n enter 0 to stop and 1 to continue =");
        scanf("%d",&choice);
    }
}
void display()
{
    struct node *temp;
    temp=head;
    if(head==0)
    {
        printf("the list is empty\n");
    }
    while(temp->next!=head)
    {
        printf("%d ",temp->data);
        temp=temp->next;
    }
    printf("%d",temp->data);
    printf("\n");
}
int count()
{
    struct node *temp;
    temp=head;
    int c=0;
    do
    {
        c++;
        temp=temp->next;
    }while(temp!=head);
    printf("the number of elements in the list is %d\n",c);
    return c;
}
void insert_beg()
{
    struct node *newnode,*temp;
    newnode=(struct node *)malloc(sizeof(struct node));
    printf("enter the data =");
    scanf("%d",&newnode->data);
    if(head==0)
    {
        head=newnode;
        newnode->next=newnode;
    }
    else
    {
        temp=head;
        while(temp->next!=head)
        {
            temp=temp->next;
        }
        temp->next=newnode;
        newnode->next=head;
        head=newnode;
    }
}
void insert_end()
{
    struct node *newnode,*temp;
    newnode=(struct node *)malloc(sizeof(struct node));
    printf("enter the data =");
    scanf("%d",&newnode->data);
    if(head==0)
    {
        head=newnode;
        newnode->next=newnode;
    }
    else
    {
        temp=head;
        while(temp->next!=head)
        {
            temp=temp->next;
        }
        newnode->next=head;
        temp->next=newnode;
    }
}
void insert_at_pos()
{
    struct node *newnode,*temp;
    int i=1;
    int pos;
    int leg=count();
    printf("enter the position in between 1 to %d\n",leg);
    printf("enter the position =");
    scanf("%d",&pos);
    if(pos>leg)
    {
        printf("Invalid position\n");
    }
    else
    {
        temp=head;
        while(i<pos-1)
        {
            temp=temp->next;
            i++;
        }
        newnode=(struct node *)malloc(sizeof(struct node));
        printf("enter the data =");
        scanf("%d",&newnode->data);
        newnode->next=temp->next;
        temp->next=newnode;
    }
}
void delete_beg()
{
    struct node *temp,*firstnode;
    temp =head;
    while(temp->next!=head)
    {
        temp=temp->next;
    }
    firstnode=head;
    head=head->next;
    temp->next=firstnode->next;
    free(firstnode);
}
void delete_end()
{
    struct node *temp,*endnode;
    temp =head;
    while(temp->next!=head)
    {
        endnode=temp;
        temp=temp->next;
    }
    endnode->next=head;
    free(temp);
}
void delete_at_pos()
{
    struct node *temp,*nextnode;
    int i=1;
    int pos;
    int leg=count();
    printf("enter the position in between 1 to %d\n",leg);
    printf("enter the position =");
    scanf("%d",&pos);
    temp=head;
    while(i<pos-1)
    {
        temp=temp->next;
        i++;
    }
    nextnode=temp->next;
    temp->next=nextnode->next;
    free(nextnode);
}

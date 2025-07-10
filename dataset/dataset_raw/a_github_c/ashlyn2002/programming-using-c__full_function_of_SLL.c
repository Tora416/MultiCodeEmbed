

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
void reverse();
struct node
    {
        int data;
        struct node *next;
    };
    struct node *head=0;
int main()
{
    printf("Linked list functions\n");
    int choice;
    printf("1.implementation\n");
    printf("2.display\n");
    printf("3.count\n");
    printf("4.insert the element at the beginning position of linked list\n");
    printf("5.insert the element at the last position of linked list\n");
    printf("6.insert the element at any position of linked list\n");
    printf("7.delete the element at the beginning position of linked list\n");
    printf("8.delete the element at the last position of linked list \n");
    printf("9.delete the element at any position of linked list\n");
    printf("10.reverse the linked list\n");
    printf("11.exit\n");
    printf("enter the choice =");
    scanf("%d",& choice);
    while(choice!=12)
    {
    switch(choice)
    {
    case 1:printf("implementation \n");
    create();
    break;
    case 2:printf("display\n");
    display();
    break;
    case 3:printf("count the element in linked list\n");
    count();
    break;
    case 4:printf("insert the element at the beginning position of linked list\n");
    insert_beg();
    break;
    case 5:printf("insert the element at the last position of linked list\n");
    insert_end();
    break;
    case 6:printf("insert the element at any position of linked list\n");
    insert_at_pos();
    break;
    case 7:printf("delete the element at the beginning position of linked list\n");
    delete_beg();
    break;
    case 8:printf("delete the element at the last position of linked list\n");
    delete_end();
    break;
    case 9:printf("delete the element at any position of linked list\n");
    delete_at_pos();
    break;
    case 10:printf("reverse the linked list\n");
    reverse();
    break;
    case 11:printf("exit\n");
    exit(0);
    break;
    default: printf("wrong choice \n");
    break;
    }
    printf("enter the choice =");
    scanf("%d",& choice);
    }
}
void create()
{
    struct node *newnode,*temp;
    int choice;
    while(choice)
    {
        newnode=(struct node*)malloc(sizeof(struct node));
            printf("enter the data = ");
            scanf("%d",& newnode->data);
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
       printf("do you need to continue (0,1)?\n0 to stop 1 to continue the element in the linked list =");
           scanf("%d",& choice);
    }
}
void display()
{
    struct node *temp;
    temp=head;
    while(temp!=0)
    {
        printf("%d ",temp->data);
        temp=temp->next;
    }
    printf("\n");
}
int count()
{
    struct node *temp;
    int count=0;
    temp=head;
    while(temp!=0)
    {
        count++;
        temp=temp->next;
    }
    printf("the number of element in linked list is %d", count);
    printf("\n");
    return count;
}
void insert_beg()
{
    struct node *newnode;
    newnode=(struct node*)malloc(sizeof(struct node));
    printf("enter the data =");
    scanf("%d",&newnode->data);
    newnode->next=head;
    head=newnode;
}
void insert_end()
{
    struct node *newnode,*temp;
    newnode=(struct node*)malloc(sizeof(struct node));
    printf("enter the data =");
    scanf("%d",&newnode->data);
    newnode->next=0;
    temp=head;
    while(temp->next!=0)
    {
        temp=temp->next;
    }
    temp->next=newnode;
}
void insert_at_pos()
{
    struct node *newnode,*temp;
    int pos;
    printf("enter the position to insert the element =");
    scanf("%d",&pos);
    int i=1;
    int leg=count();
    if(pos>leg)
    {
        printf("invalid position\n");
    }
    else
    {
        newnode=(struct node*)malloc(sizeof(struct node));
        printf("enter the data =");
        scanf("%d",&newnode->data);
        temp=head;
        while(i<pos-1)
        {
            temp=temp->next;
            i++;
        }
        newnode->next=temp->next;
        temp->next=newnode;
    }
}
void delete_beg()
{
    struct node *temp;
    temp=head;
    head=head->next;
    free(temp);
}
void delete_end()
{
    struct node *temp,*nextnode;
    temp=head;
    while(temp->next!=0)
    {
        nextnode=temp;
        temp=temp->next;
    }
    if(temp==head)
    {
        head=0;
        free(temp);
    }
    else
    {
        nextnode->next=0;
        free(temp);
    }
}
void delete_at_pos()
{
    struct node *temp,*nextnode;
    int pos;
    printf("enter the position to delete the element =");
    scanf("%d",&pos);
    int i=1;
    int leg=count();
    if(pos>leg)
    {
        printf("invalid position\n");
    }
    else
    {
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
}
void reverse()
{
    struct node *nextnode,*prenode,*currentnode;
    prenode=0;
    currentnode=nextnode=head;
    while(nextnode!=0)
    {
        nextnode=nextnode->next;
        currentnode->next=prenode;
        prenode=currentnode;
        currentnode=nextnode;
    }
    head=prenode;
}



#include <stdio.h>
#include <stdlib.h>

void creat();
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
struct node *pre;
};
struct node *head=0;
int main()
{
    printf("function of double linked list \n");
    printf("1.implementation of linked list\n");
    printf("2.display the linked list\n");
    printf("3.count the number of element in the linked list\n");
    printf("4.insert the element at the beginning position of linked list\n");
    printf("5.insert the element at the last position of linked list\n");
    printf("6.insert the element at any position of linked list\n");
    printf("7.delete the element from beginning position from the linked list\n");
    printf("8.delete the element from last position from the linked list\n");
    printf("9.delete the element from any position from the linked list\n");
    printf("10.revers the linked list\n");
    printf("11.exit\n");
    int choice;
    printf("enter the choice =");
    scanf("%d",&choice);
    while(choice!=12)
    {
        switch(choice)
        {
            case 1: printf("implementation\n");
            creat();
            break;
            case 2:printf("display the linked list\n");
            display();
            break;
            case 3:printf("count the number of element in the linked list\n");
            count();
            break;
            case 4:printf("insert the element at the beginning position of linked list\n");
            insert_beg();
            break;
            case 5: printf("insert the element at the last position of linked list\n");
            insert_end();
            break;
            case 6:printf("insert the element at any position of linked list\n");
            insert_at_pos();
            break;
            case 7:printf("delete the element from beginning position from the linked list\n");
            delete_beg();
            break;
            case 8:printf("delete the element from last position from the linked list\n");
            delete_end();
            break;
            case 9:printf("delete the element from any position from the linked list\n");
            delete_at_pos();
            break;
            case 10:printf("revers the linked list\n");
            reverse();
            break;
            case 11:printf("exit \n");
            exit(0);
            break;
            default:printf("invalied choice \n");
            break;
        }
         printf("enter the choice =");
        scanf("%d",&choice);
    }
}
void creat()
{
struct node *newnode,*temp;
int choice;
    while(choice)
    {
        newnode=(struct node *)malloc(sizeof(struct node));
            printf("enter the data =");
            scanf("%d",&newnode->data);
            newnode->pre=0;
            newnode->next=0;
        if(head==0)
        {
            head=temp=newnode;
        }
        else
        {
            temp->next=newnode;
            newnode->pre=temp;
            temp=newnode;
        }
        printf("do you need to continue(0,1)?\n enter 0 to stop  enter 1 to continue = ");
        scanf("%d",&choice);
    }
}
void display()
{
    struct node *temp;
    temp=head;
    if(head==0)
    {
        printf("the list is empty");
    }
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
    temp=head;
    int c=0;
    while(temp!=0)
    {
        c++;
        temp=temp->next;
    }
    printf("the number of elements in the linked list is %d \n",c);
    return c;
}
void insert_beg()
{
    struct node *newnode;
    newnode=(struct node *)malloc(sizeof(struct node));
    printf("enter the data =");
    scanf("%d",&newnode->data);
    newnode->pre=0;
    newnode->next=head;
    head=newnode;
}
void insert_end()
{
    struct node *newnode,*temp;
    newnode=(struct node *)malloc(sizeof(struct node));
    printf("enter the data =");
    scanf("%d",&newnode->data);
    newnode->next=0;
    temp=head;
    while(temp->next!=0)
    {
        temp=temp->next;
    }
    temp->next=newnode;
    newnode->pre=temp;
}
void insert_at_pos()
{
    struct node *newnode,*temp;
    int i=1,pos;
    printf("enter the position =");
    scanf("%d",&pos);
    int leg=count();
    if(pos>leg)
    {
        printf("invalied position\n");
    }
    else
    {
        newnode=(struct node *)malloc(sizeof(struct node));
        printf("enter the data =");
        scanf("%d",&newnode->data);
        temp=head;
        while(i<pos-1)
        {
            temp=temp->next;
            i++;
        }
        newnode->pre=temp;
        newnode->next=temp->next;
        temp->next=newnode;
        newnode->next->pre=newnode;
    }
}
void delete_beg()
{
    struct node *temp;
    if(head==0)
    {
        printf("the list is empty\n");
    }
    else if(head->next==0)
    {
        head=0;
        free(head);
    }
    else
    {
        temp=head;
        head->next->pre=0;
        head=head->next;
        free(temp);
    }
}
void delete_end()
{
    struct node *temp;
    if(head==0)
    {
        printf("the list is empty\n");
    }
    else if(head->next==0)
    {
        head=0;
        free(head);
    }
    else
    {
        temp=head;
        while(temp->next!=0)
        {
            temp=temp->next;
        }
        temp->pre->next=0;
        free(temp);
    }
}
void delete_at_pos()
{
    struct node *temp;
    int pos;
    int i=1;
    printf("enter the position =");
    scanf("%d",&pos);
    temp=head;
    while(i<pos)
    {
        temp=temp->next;
        i++;
    }
    if(temp->next==0)
    {
        temp->pre->next=0;
        free(temp);
    }
    else
    {
        temp->next->pre=temp->pre;
        temp->pre->next=temp->next;
        free(temp);
    }
}
void reverse()
{
    struct node *currentnode,*nextnode,*prenode;
    prenode=0;
    currentnode=nextnode=head;
    while(nextnode!=0)
    {
        nextnode=nextnode->next;
        currentnode->next=prenode;
        currentnode->pre=nextnode;
        prenode=currentnode;
        currentnode=nextnode;
    }
    head=prenode;
}

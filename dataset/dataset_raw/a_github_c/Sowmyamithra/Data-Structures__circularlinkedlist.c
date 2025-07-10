#include<stdio.h>
#include<stdlib.h>
struct list
{
    int val;
    struct list* next;
}*front=NULL,*rear=NULL,*temp=NULL,*q=NULL;
int value,i=0;
void insert(int tar)
{
    struct list* p=(struct list*)malloc(sizeof(struct list));
    p->val=tar;
    p->next=NULL;
    if(rear==NULL)
    {
        front=rear=p;
    }
    else
    {
        rear->next=p;
        rear=p;
        rear->next=front;
    }
}
void delete(int tar)
{
    if(rear==NULL)
    {
        printf("\nlist is empty");
    }
    else
    {
        temp=front;
        q=front;
        while(temp!=rear)
        {
            if(temp->val==tar)
            {
                if(temp==front)
                {
                    front=front->next;
                    rear->next=front;
                    free(temp);
                    temp=front;
                }
                else
                {
                    q->next=temp->next;
                    free(temp);
                    temp=q->next;
                }
            }
            q=temp;
            temp=temp->next;
        }
        if(temp->val==tar)
        {
            q->next=front;
            temp=NULL;
            free(temp);
        }
    }
}
void search(int tar)
{
    if(rear==NULL)
    {
        printf("\nlist is empty");
    }
    else
    {
        for(temp=front;temp!=rear;temp=temp->next)
        {
            if(temp->val==tar)
            {
                printf("\nvalue found");
                i++;
            }
        }
        if(temp->val==tar)
        {
            printf("\nvalue found");
            i++;
        }
    }
    if(i==0)
    printf("\nvalue not found in the list");
}
void display()
{
    if(rear==NULL)
    printf("\nlist is empty");
    else
    {
        printf("\nList is:\n");
        for(temp=front;temp!=rear;temp=temp->next)
        {
            printf("\t%d",temp->val);
        }
        printf("\t%d",temp->val);
        printf("\t%d",temp->next->val);
    }
}
void main()
{
    int ch;
    while(1)
    {
        printf("\nEnter choice:");
        scanf("%d",&ch);
        switch(ch)
        {
            case 1:
            {
                printf("\nEnter the value to insert:");
                scanf("%d",&value);
                insert(value);
                break;
            }
            case 2:
            {
                printf("\nEnter the value to delete:");
                scanf("%d",&value);
                delete(value);
                break;
            }
            case 3:
            {
                printf("\nEnter the value to search:");
                scanf("%d",&value);
                search(value);
                break;
            }
            case 4:
            {
                display();
                break;
            }
            default:
            {
                exit(0);
                break;
            }
        }
    }
}
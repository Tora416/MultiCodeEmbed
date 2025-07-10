#include<stdio.h>
#include<stdlib.h>
struct List
{
    int val;
    struct List *prev;
    struct List *next;
}*start=NULL,*temp=NULL,*q=NULL;
int value,pos,i=0;
void insert(int tar,int pos)
{
    struct List* p=(struct List*)malloc(sizeof(struct List));
    p->val=tar;
    p->prev=NULL;
    p->next=NULL;
    if(start==NULL)
    {
        start=p;
    }
    else
    {
        if(pos==0)
        {
            p->next=start;
            start=p;
        }
        else
        {
            temp=start;
            for(i=0;i<(pos-1);i++)
            {
                temp=temp->next;
            }
            p->next=temp->next;
            p->prev=temp;
            temp->next->prev=p;
            temp->next=p;   
        }
    }
}
void delete(int tar)
{
    if(start==NULL)
    printf("\nList is empty");
    else
    {
        temp=start;
        q=temp;
        while(temp->next!=NULL)
        {
            if(temp->val==start->val && temp->val==tar)
            {
                start=start->next;
                start->prev=NULL;
                free(temp);
                temp=start;
            }
            else if(temp->val==tar)
            {
                q->next=temp->next;
                temp->next->prev=q;
                free(temp);
                temp=q->next;
            }
            q=temp;
            temp=temp->next;
        }
        if(temp->val==tar && temp->next==NULL)
        {
            q->next=NULL;
            temp->prev=NULL;
            free(temp);
        }
    }
}
void search(int tar)
{
    int ct=0;
    if(start==NULL)
    printf("\nList is empty");
    else
    {
        temp=start;
        while(temp->next!=NULL)
        {
            if(temp->val==tar)
            {
                printf("\nElement found");
                ct++;
                break;
            }
            temp=temp->next;
        }
        if(temp->val==tar && temp->next==NULL)
        {
            printf("\nElement found");
            ct++;
        }
        if(ct==0)
        {
            printf("\nthe element is not found in the list");
        }
    }
}
void display()
{
    if(start==NULL)
    printf("\nList is empty");
    else
    {
        temp=start;
        while(temp->next!=NULL)
        {
            printf("\t%d",temp->val);
            temp=temp->next;
        }
    }
    printf("\t%d",temp->val);
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
                printf("\nEnter the value and position to insert:");
                scanf("%d%d",&value,&pos);
                insert(value,pos);
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
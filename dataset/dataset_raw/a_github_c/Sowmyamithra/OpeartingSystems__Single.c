
#include<stdio.h>
#include<stdlib.h>
struct dir
{
    char file;
    struct dir* next;
}*start,*temp,*q;
int isthere(char name)
{
    int flag=-1;
    temp=start;
    while(temp!=NULL)
    {
        if(temp->file==name)
        {
            flag=1;
            break;
        }
        temp=temp->next;
    }
    return(flag);
}
void add_file(char name)
{
    struct dir* p=(struct dir*)malloc(sizeof(struct dir));
    p->file=name;
    p->next=NULL;
    if(isthere(name)==-1)
    {
        if(start==NULL)
            start=p;
        else
        {
            temp=start;
            while(temp->next!=NULL)
                temp=temp->next;
            temp->next=p;
        }
    }
    else
        printf("\nFile already exists");
}
void rem_file(char name)
{
    if(isthere(name)==-1)
        printf("\nFile does not exist");
    else
    {
        temp=start;
        q=temp;
        while(temp->next!=NULL)
        {
            if(temp->file==name)
            {
                if(temp==start)
                {
                    start=start->next;
                    free(temp);
                    temp=start;
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
        if(temp->file==name)
        {
            q->next=NULL;
            free(temp);
        }
    }
}
void display()
{
    temp=start;
    printf("\nFiles are : ");
    while(temp!=NULL)
    {
        printf("%c\t",temp->file);
        temp=temp->next;
    }
}
void main()
{
    int ch;
    char name[5];
    while(1)
    {
        printf("\nEnter choice : ");
        scanf("%d",&ch);
        switch(ch)
        {
            case 1: 
            {
                printf("\nEnter file name : ");
                scanf("%s",name);
                add_file(name[0]);
                break;
            }
            case 2: 
            {
                printf("\nEnter file name : ");
                scanf("%s",name);
                rem_file(name[0]);
                break;
            }
            case 3:
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
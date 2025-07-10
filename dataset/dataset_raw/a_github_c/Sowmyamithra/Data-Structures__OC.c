
#include<stdio.h>
#include<stdlib.h>
struct hash
{
    int val;
    struct hash* next;
}*temp,*q;
struct hash* HASH[5];
int val,key;
int H(int key)
{
    return(key%10);
}
void insert(int key,int value)
{
    int index=H(key);
    struct hash* p=(struct hash*)malloc(sizeof(struct hash));
    p->val=value;
    p->next=NULL;
    if(HASH[index]==NULL)
    {
        HASH[index]=p;
    }
    else
    {
        temp=HASH[index];
        while(temp->next!=NULL)
            temp=temp->next;
        temp->next=p;
    }
}
void delete(int key,int value)
{
    int index=H(key);
    int ct=0;
    if(HASH[index]!=NULL)
    {
        temp=HASH[index];
        q=temp;
        while(temp->next!=NULL)
        {
            if(temp->val==value)
            {
                if(temp==HASH[index])
                {
                    HASH[index]=temp->next;
                    free(temp);
                    temp=HASH[index];
                    printf("\nValue deleted");
                    ct++;
                }
                else
                {
                    q->next=temp->next;
                    free(temp);
                    printf("\nValue deleted");
                    ct++;
                }
            }
            q=temp;
            temp=temp->next;
        }
        if(temp->val==value)
        {
            q->next=NULL;
            free(temp);
            printf("\nValue deleted");
            ct++;
        }
        if(ct==0)
        printf("\nValue is not found");
    }
}
void search(int key,int value)
{
    int index=H(key);
    int ct=0;
    if(HASH[index]!=NULL)
    {
        temp=HASH[index];
        while(temp->next!=NULL)
        {
            if(temp->val==value)
            {
                printf("\nValue found");
                ct++;
            }
            temp=temp->next;
        }
        if(temp->val==value)
        {
            printf("\nValue found");
            ct++;
        }
        if(ct==0)
        printf("\nValue not found");
    }
}
void display()
{
    int i;
    for(i=0;i<5;i++)
    {
        if(HASH[i]!=NULL)
        {
            printf("\nvalues with index %d \n",i);
            temp=HASH[i];
            while(temp->next!=NULL)
            {
                printf("\t%d",temp->val);
                temp=temp->next;
            }
            printf("\t%d",temp->val);
        }
    }
}
void main()
{
    int ch,i;
    for(i=0;i<5;i++)
    HASH[i]=NULL;
    printf("\n1.INSERT\n2.DELETE\n3.SEARCH\n4.DISPLAY\n\n");
    while(1)
    {
        printf("\nEnter choice:");
        scanf("%d",&ch);
        switch(ch)
        {
            case 1:
            {
                printf("\nEnter the key:");
                scanf("%d",&key);
                printf("\nEnter the value:");
                scanf("%d",&val);
                insert(key,val);
                break;
            }
            case 2:
            {
                printf("\nEnter the key:");
                scanf("%d",&key);
                printf("\nEnter the value:");
                scanf("%d",&val);
                delete(key,val);
                break;
            }
            case 3:
            {
                printf("\nEnter the key:");
                scanf("%d",&key);
                printf("\nEnter the value:");
                scanf("%d",&val);
                search(key,val);
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
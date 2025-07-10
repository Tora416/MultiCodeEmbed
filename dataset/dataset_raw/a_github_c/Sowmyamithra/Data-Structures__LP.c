
#include<stdio.h>
#include<stdlib.h>
int HASH[10],key,val,i;
int H(int value)
{
    return(value%10);
}
void insert(int key,int value)
{
    int index=H(key);
    int i;
    if(HASH[index]==-1)
    {
        HASH[index]=value;
    }
    else
    {
        for(i=index+1;i<10;i++)
        {
            if(HASH[i]==-1)
            {
                HASH[i]=value;
                break;
            }
        }
    }
}
void delete(int key,int value)
{
    int index=H(key);
    int ct=0,i;
    if(HASH[index]==value)
    {
        HASH[index]=-1;
        printf("\nValue deleted");
        ct++;
    }
    else
    {
        for(i=index+1;i<10;i++)
        {
            if(HASH[i]==value)
            {
                HASH[i]=-1;
                printf("\nValue deleted");
                ct++;
                break;
            }
        }
    }
    if(ct==0)
    {
        printf("\nThe key with that value is not found");
    }
}
void search(int key,int value)
{
    int index=H(key);
    int i;
    int ct=0;
    if(HASH[index]==value)
    {
        printf("\nThe value found at index %d ",index);
        ct++;
    }
    else
    {
        for(i=index+1;i<10;i++)
        {
            if(HASH[i]==value)
            {
                printf("\nValue found at index %d ",i);
                ct++;
                break;
            }
        }
    }
    if(ct==0)
    {
        printf("\nThe key with that value is not found");
    }   
}
void display()
{
    int i;
    for(i=0;i<10;i++)
    {
        if(HASH[i]!=-1)
        printf("\nkey : %d\tvalue : %d",i,HASH[i]);
    }
}
void main()
{
    int ch,i;
    for(i=0;i<10;i++)
    HASH[i]=-1;
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
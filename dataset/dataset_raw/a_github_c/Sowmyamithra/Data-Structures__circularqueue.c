#include<stdio.h>
#include<stdlib.h>
#define MAX 5
int queue[MAX];
int value;
int i=0,x=0;
int f=-1,r=-1;
void enqueue(int val)
{
    if(r==-1)
    {
        f=(f+1)%MAX;
        r=(r+1)%MAX;
        queue[r]=val;
    }
    else if((r==MAX-1 && f==0) || r==f-1)
    {
        printf("\nQueue is FULL");
    }
    else
    {
        r=(r+1)%MAX;
        queue[r]=val;
    }
}
int dequeue()
{
    if((f==-1 && r==-1))
    {
        printf("\nQueue is Empty");
        return(-1);
    }
    else
    {
        if(f==(r+1)%MAX && queue[f]==-1)    
        {
            printf("\nQueue is Empty");
            return(-1);
        }
        else
        {
            value=queue[f];
            queue[f]=-1;
            f=(f+1)%MAX;
            return(value);
        }
    }
}
void search(int val)
{
    i=0;
    if((f==-1 && r==-1))
    printf("\nQueue is Empty");
    else if(f==(r+1)%MAX && queue[f]==-1)
    printf("\nQueue is Empty");
    else
    {   
        i=f;
        while(i!=r)
        {
            if(queue[i]==val)
            {
                printf("\nvalue found");
                x++;
            }
            i=(i+1)%MAX;
        }
        if(queue[i]==val)
        {
            printf("\nvalue found");
            x++;
        }
        if(x==0)
        printf("\nthe value is not found in the queue");
    }

}
void display()
{
    if((f==-1 && r==-1))
    printf("\nQueue is Empty");
    else if(f==(r+1)%MAX && queue[f]==-1)
    printf("\nQueue is Empty");
    else
    {
        printf("\nQueue is:\n");
        i=f;
        while(i!=r)
        {           
            printf("\t%d",queue[i]);
            i=(i+1)%MAX;
        }
        printf("\t%d",queue[r]);
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
                printf("\nEnter value to insert:");
                scanf("%d",&value);
                enqueue(value);
                break;
            }
            case 2:
            {
                printf("\nthe popped value is %d",dequeue()); 
                break;
            }
            case 3:
            {
                printf("\nEnter the value to search");
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

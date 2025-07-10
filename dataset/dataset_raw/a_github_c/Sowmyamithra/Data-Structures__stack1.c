
#include<stdio.h>
#include<stdlib.h>
#define MAX 100
int stack[MAX];
int value,top=-1,key;
void push(int stack[],int val)
{
    if(top==MAX-1)
    printf("\nstack is full");
    else
    {
        top=top+1;
        stack[top]=val;
    }
}
void pop(int stack[])
{
    if(top==-1)
    {
        printf("\nstack is empty");
    }
    else
    {
        printf("\nThe value popped is : %d",stack[top]);
        top=top-1;
    }
}
void search(int stack[],int val)
{
    int i,c=0;
    if(top==-1)
    printf("\nstack is empty");
    else
    {
        for(i=0;i<=top;i++)
        {
            if(stack[i]==val)
            {
                printf("\nvalue found");
                c=c+1;
                break;
            }
        }
        if(c==0)
        printf("\nvalue not found");
    }
}
void display(int stack[])
{
    int i;
    if(top==-1)
    printf("\nstack is empty");
    else
    {
        printf("\nstack is :\n");
        for(i=0;i<=top;i++)
        printf("\t%d",stack[i]);
    }
}
void main()
{
    int ch;
    printf("1.INSERT\n2.DELETE\n3.SEARCH\n4.PRINT\n\n");
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
                push(stack,value);
                break;
            }
            case 2:
            {
                pop(stack);
                break;
            }
            case 3:
            {
                printf("\nEnter the value to search:");
                scanf("%d",&value);
                search(stack,value);
                break;
            }
            case 4:
            {
                display(stack);
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
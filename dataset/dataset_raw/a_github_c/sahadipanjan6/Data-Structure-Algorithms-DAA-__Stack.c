#include<stdio.h>
#include<stdlib.h>

#define size 10


struct Stack
{
    int array[size];
    int top;
}ptr;



void push();
void pop();
void display();
int checkStackFull();
int checkStackEmpty();


void main()
{
    int choice = 0;
    int contin = 0;
    ptr.top = -1;

    do{
        printf("\nPress 1 for PUSH");
        printf("\nPress 2 for POP");
        printf("\nPress 3 for DISPLAY");
        printf("\nPress 4 for EXIT");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                
                push();
                break;

            case 2:
                
                pop();
                break;

            case 3:
                
                display();
                break;

            case 4:
                
                exit(0);
                break;

            default:
                printf("\nEnter a valid choice!!!");
        }
        printf("\nPress 1 to continue, else press any other number to EXIT: ");
        scanf("%d", &contin);
    }while(contin == 1);
}



void push()
{
    int flag = checkStackFull();
    if(flag == 1)
    {
        int element = 0;
        printf("\nEnter the element to be pushed: ");
        scanf("%d", &element);
        ptr.array[++(ptr.top)] = element;
    }
    else
        printf("\nStack is FULL!!!");
}


void pop()
{
    int flag = checkStackEmpty();
    if(flag == 1)
    {
        printf("\nPopped Element: %d", (ptr.array[(ptr.top)--]));
    }
    else
        printf("\nStack is EMPTY!!!");
}


void display()
{
    int i = 0;
    int flag = checkStackEmpty();

    if(flag == 1)
    {
        printf("\nElements present in the Stack are:- \n");
        for(i=(ptr.top); i>-1; i--)
        {
            printf("%d\t", (ptr.array[i]));
        }
        printf("\n");
    }
    else
        printf("\nStack is EMPTY!!!");
}


int checkStackFull()
{
    if((ptr.top) == size-1)
        return 0;

    return 1;
}


int checkStackEmpty()
{
    if((ptr.top) == -1)
        return 0;

    return 1;
}
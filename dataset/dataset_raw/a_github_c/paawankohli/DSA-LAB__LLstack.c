#include <stdio.h>
#include <stdlib.h>

typedef struct node* nptr;
typedef struct node
{
    nptr next;
    int data;
}node;

nptr createNode(int x)
{
    nptr temp = (nptr)malloc(sizeof(node));
    temp -> data = x;
    temp -> next = NULL;

    return temp;
}

void push(nptr &stack, int x)
{
    nptr temp = createNode(x);
    temp -> next = stack;
    stack = temp;
}

int pop(nptr &stack)
{
    if(stack == NULL)
        return -1;

    nptr temp = stack;
    stack = stack -> next;

    int x = temp -> data;
    free(temp);
    return x;
}

void display(nptr &stack)
{
    if (stack == NULL)
    {   
        printf("EMPTY\n");
        return;
    }

    nptr curr = stack;

    while(curr)
    {
        printf("    %d \n", curr -> data);
        curr = curr -> next;
    }
}

int main()
{
    printf("1. Push    2. Pop    3. Display    0.Exit\n");
    int ch, ele;

    nptr stack = NULL;

    do
    {
        printf("Command: "); scanf("%d", &ch);

        switch(ch)
        {
            case 1:     
                    printf("Element: "); scanf("%d", &ele);
                    push(stack, ele);
                    break;
            
            case 2:
                    ele = pop(stack);
                    
                    if(ele == -1)
                        printf("Stack empty!\n");
                    else
                        printf("%d popped!\n", ele);
                        
                    break;

            case 3:
                    display(stack);
        }

    }while(ch != 0);
}
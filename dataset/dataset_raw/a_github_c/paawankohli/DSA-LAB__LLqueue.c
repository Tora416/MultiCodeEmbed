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

void push(nptr &head, int x)
{
    nptr temp = createNode(x);
    temp -> next = head;
    head = temp;
}

int pop(nptr &head)
{
    if (head == NULL)
        return -1;

    nptr rear2 = head;
    nptr rear = head -> next;

    while(rear -> next != NULL)
    {
        rear2 = rear2 -> next;
        rear = rear -> next;
    }

    rear2 -> next = NULL;
    int x = rear -> data;

    free(rear);
    return x;
}

void display(nptr &head)
{
    if (head == NULL)
    {   
        printf("EMPTY\n");
        return;
    }

    nptr curr = head;

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

    nptr queue = NULL;

    do
    {
        printf("Command: "); scanf("%d", &ch);

        switch(ch)
        {
            case 1:     
                    printf("Element: "); scanf("%d", &ele);
                    push(queue, ele);
                    break;
            
            case 2:
                    ele = pop(queue);
                    
                    if(ele == -1)
                        printf("Queue empty!\n");
                    else
                        printf("%d popped!\n", ele);
                        
                    break;

            case 3:
                    display(queue);
        }

    }while(ch != 0);
}
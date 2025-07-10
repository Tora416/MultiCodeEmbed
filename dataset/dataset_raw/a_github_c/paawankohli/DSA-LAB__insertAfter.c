#include <stdio.h>
#include <stdlib.h>

typedef struct node* nptr;
typedef struct node
{
    int data;
    nptr next;
}node;

nptr createNode(int x)
{
    nptr temp = (nptr)malloc(sizeof(node));
    temp -> data = x;
    temp -> next = NULL;

    return temp;
}

void insertFront(nptr &head, int ele)
{
    nptr temp = createNode(ele);
    temp -> next = head;
    head = temp;
}

void insertAfter(nptr &head, int x, int key)
{
    nptr temp = head;

    while(temp != NULL)
    {
        if (temp -> data == key)
        {
            nptr newNode = createNode(x);
            newNode -> next = temp -> next;
            temp -> next = newNode;
            return;
        }
        
        temp = temp -> next;
    }

    printf("Element wasn't found\n");
}

void display(nptr head)
{
    nptr temp = head;

    while(temp != NULL)
    {
        printf("%d --> ", temp -> data);
        temp = temp->next;
    }

    printf("NULL\n");
}

int main()
{
    nptr head = NULL;
    int ch, ele, key;

    printf("0. Exit      1. Insert Front      2. Insert After      3. Display\n");

    do
    {
        printf("Command: ");
        scanf("%d", &ch);

        switch(ch)
        {
            case 1: printf("Element: ");
                    scanf("%d", &ele);
                    insertFront(head, ele);
                    break;

            case 2: printf("Element and key element to insert after: ");
                    scanf("%d %d", &ele, &key);
                    insertAfter(head, ele, key);
                    break;

            case 3: display(head);
        }

    }while(ch != 0);
}
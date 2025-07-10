#include <stdlib.h>
#include <stdio.h>

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

void insert(nptr &head, int ele)
{
    if (head == NULL)
    {
        head = createNode(ele);
        return;
    }

    else if (ele < head -> data)
    {
        nptr temp = createNode(ele);
        temp -> next = head;
        head = temp;
        return;
    }

    else
    {
        nptr prev = NULL, curr = head;

        while(curr != NULL && curr -> data <= ele)
        {
            prev = curr;
            curr = curr -> next;
        }

        nptr temp = createNode(ele);
        prev -> next = temp;
        temp -> next = curr;
    }
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
    int ch, ele;

    printf("0. Exit      1. Insert      2. Display\n");

    do
    {
        printf("Command: ");
        scanf("%d", &ch);

        switch(ch)
        {
            case 1: printf("Element: ");
                    scanf("%d", &ele);
                    insert(head, ele);
                    break;

            case 2: display(head);
        }

    }while(ch != 0);
}
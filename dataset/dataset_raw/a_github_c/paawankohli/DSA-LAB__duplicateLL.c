#include <stdio.h>
#include <stdlib.h>

typedef struct node* nptr;
typedef struct node
{
    int data;
    nptr next;
} node;

nptr createNode(int x)
{
    nptr temp = (nptr)malloc(sizeof(node));
    temp -> data = x;
    temp -> next = NULL;

    return temp;
}

void insertRear(nptr &head, int x)
{
    if (head == NULL)
    {
        head = createNode(x);
        return;
    }

    nptr temp = head;

    while (temp -> next != NULL)
        temp = temp -> next;

    temp -> next = createNode(x);
}

void display(nptr head)
{
    nptr temp = head;

    while (temp)
    {
        printf("%d --> ", temp -> data);
        temp = temp -> next;
    }

    printf("NULL\n");
}

void removeDuplicate(nptr head)
{
    if (head == NULL || head -> next == NULL)
        return;

    nptr temp1 = head, temp2 = head -> next;

    if (temp1 -> data == temp2 -> data)
    {
        temp1 -> next = temp2 -> next;
        free(temp2);
    }
    else
        temp1 = temp1 -> next;

    removeDuplicate(temp1);
}

void removeDuplicate2(nptr head)
{
    if (head == NULL)
        printf("Empty list\n");

    nptr curr = head, dup = NULL;

    while(curr != NULL && curr -> next != NULL)
    {
        if (curr -> data == curr -> next -> data)
        {
            dup = curr -> next;
            curr -> next = dup -> next;
            free(dup);
        }
        else
            curr = curr -> next;
    }
}

int main()
{
    printf("1. Insert Rear     2. Display     3. Remove Duplicates     0. Exit\n");
    int ch, ele;

    nptr head = NULL;

    do
    {
        printf("Command: "); scanf("%d", &ch);

        switch(ch)
        {
            case 1:
                    
                    scanf("%d", &ele);
                    insertRear(head, ele);
                    break;

            case 2:
                    display(head);
                    break;

            case 3: 
                    removeDuplicate2(head);
        }

    }while(ch != 0);
}
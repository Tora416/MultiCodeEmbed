
#include <stdio.h>
#include <stdlib.h>

struct node
{
    int data;
    struct node* next;
}*first;

void create(int A[], int n)
{
    struct node *last, *t;
    int i;
    first = (struct node*)malloc(sizeof(struct node));
    first->data = A[0];
    first->next = NULL;
    last = first;

    for(i = 1 ; i < n ; i++)
    {
        t = (struct node*)malloc(sizeof(struct node));
        t->data = A[i];
        t->next = NULL;
        last->next = t;
        last = t;
    }
}

void display(struct node *p)
{
    while(p)
    {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}

void check_empty(struct node *p)
{
    if(!p)
    {
        printf("\nList is empty\n");
    }
    else
    {
        printf("\nList is not empty\n");
    }
}

int length(struct node *p)
{
    int len = 0;
    while(p)
    {
        len++;
        p = p->next;
    }
    return len;
}

void insert(struct node *p, int index, int x)
{
    if(index < 0 || index > length(first))
    {
        printf("\nInvalid index\n");
        return;
    }
    struct node *t = (struct node*)malloc(sizeof(struct node));
    t->data = x;

    if(index == 0)
    {
        t->next = first;
        first = t;
    }
    else
    {
        for(int i = 0; i < index - 1 ; i++)
            p = p->next;
        t->next = p->next;
        p->next = t;
    }
}

int delete_index(struct node *p, int index)
{
    if(index < 0 || index > length(first))
    {
        printf("\nInvalid index\n");
        return -1;
    }

    struct node *q = p;
    int x = 0;

    if(index == 1)
    {
        q = first;
        x = first->data;
        first = first->next;
        free(q);
        return x;
    }
    else
    {
        for(int i = 0 ; i < index - 1; i++)
        {
            q = p;
            p = p->next;
        }
        q->next = p->next;
        x = p->data;
        free(p);
        return x;
    }
}

int delete_key(struct node *p, int key)
{
    int index = 1;
    struct node *q = NULL;

    if(first->data == key)
    {
        q = first;
        if(first->next != NULL)
            first = first->next;
        else
            first = NULL;
        free (q);
        return index;

    }
    else
    {
        while(p->data != key)
        {
            q = p;
            p = p->next;
            index++;
            if(p->next ==NULL && p->data != key)
            {
                printf("\nKey is not present in list\n");
                return -1;
            }
        }
        q->next = p->next;
        free(p);
        return index;
    }
}

int search(struct node *p, int key)
{
    int index = 1;
    while(p)
    {
        if(key == p->data)
        {
            return index;
        }
        else
        {
            p = p->next;
            index++;
        }
    }
    return 0;
}

int main()
{
    int n,choice, index, x, key, len;
    printf("Enter number of elements : ");
    scanf("%d", &n);

    int A[n];
    printf("Enter elements : ");
    for(int i = 0 ; i < n ; i++)
        scanf("%d", &A[i]);

    create(A, n);
    do
    {
        printf("\n\n1 : Traversal of the list\n2 : Check if the list is empty\n");
        printf("3 : Insert a node at the certain position\n4 : Delete a node at the certain position\n");
        printf("5 : Delete a node for the given key\n6 : Count the total number of nodes\n");
        printf("7 : Search for an element in the linked list\n8: EXIT\n");
        printf("\nEnter Choice : ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1 :
                display(first);
                break;

            case 2 :
                check_empty(first);
                break;

            case 3 :
                printf("\nEnter position (0 for after zero nodes, 1 for after 1 node and so on..) : ");
                scanf("%d", &index);
                printf("Enter data : ");
                scanf("%d", &x);
                insert(first, index, x);
                printf("New list : ");
                display(first);
                break;

            case 4 :
                printf("\nEnter position (1 for 1st node, 2 for 2nd node and so on..): ");
                scanf("%d", &index);
                x = delete_index(first, index);
                printf("Data deleted at position %d : %d\n", index, x);
                printf("New list : ");
                display(first);
                break;

            case 5 :
                printf("\nEnter key : ");
                scanf("%d", &key);
                index = delete_key(first, key);
                if(index != -1)
                {
                    printf("% deleted at position : %d\n", key, index);
                    printf("New list : ");
                    display(first);
                }
                break;

            case 6 :
                len = length(first);
                printf("\nNumber of nodes : %d\n", len);
                break;

            case 7 :
                printf("\nEnter key : ");
                scanf("%d", &key);
                index = search(first, key);
                if(index != -1)
                {
                    printf("Element is present at position %d\n", index);
                }
                break;
        }
    }while(choice != 8);
}
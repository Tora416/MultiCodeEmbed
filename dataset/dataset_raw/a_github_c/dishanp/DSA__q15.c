

#include <stdio.h>
#include <stdlib.h>

struct node
{
    int data;
    struct node *next;
}*first;

void create(int A[], int n)
{
    struct node *t, *last;
    first = (struct node*)malloc(sizeof(struct node));
    first->data = A[0];
    first->next = NULL;
    last = first;

    for(int i = 1 ; i < n ; i++)
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

void delete(struct node *p, int key)
{
    int index = 1;
    struct node *q = NULL;

    if(first->data == key)
    {
        printf("\nKey found at node : %d\n\n", index);
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
            }
        }
        printf("Key found at node : %d\n", index);

        q->next = p->next;
        p->next = first;
        first = p;
        printf("Key moved to head\n\nNew list : ");
        display(first);
    }
}

int main()
{
    int n, key, index;
    printf("Number of elements : ");
    scanf("%d", &n);
    int A[n];
    printf("Enter elements : ");
    for(int i = 0 ; i < n ; i++)
    {
        scanf("%d", &A[i]);
    }
    create(A, n);
    
    

    printf("Enter key to be searched : ");
    scanf("%d", &key);
    delete(first, key);
}
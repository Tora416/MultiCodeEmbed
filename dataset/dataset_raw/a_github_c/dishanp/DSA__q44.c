

#include <stdio.h>
#include <stdlib.h>
struct node
{
    int data;
    struct node* next;
}*first;

void create(int A[], int n)
{
    struct node *t, *last;
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

void reversedisplay(struct node *p)
{
    if(p)
    {
        reversedisplay(p->next);
        printf("%d ", p->data);
    }
}

int main()
{
    int n;
    printf("Enter number of elements : ");
    scanf("%d", &n);
    int A[n];
    printf("Enter elements : ");
    for(int i = 0 ; i < n ; i++)
    {
        scanf("%d", &A[i]);
    }
    create(A, n);
    printf("\nThe list : ");
    display(first);
    printf("\n");
    printf("The elements in reverse are : ");
    reversedisplay(first);
    printf("\n");
}



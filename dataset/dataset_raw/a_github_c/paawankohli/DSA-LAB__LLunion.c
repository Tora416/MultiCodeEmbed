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

void insertRear(nptr &head, int ele)
{
    if (head == NULL)
    {
        head = createNode(ele);
        return;
    }

    nptr rear = head;
    
    while(rear -> next != NULL)
        rear = rear -> next;

    nptr temp = createNode(ele);
    rear -> next = temp;
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

int elementFound(nptr head, int x)
{
    while(head)
        if(head -> data == x)
            return 1;
        else
            head = head -> next;

    return 0;
}

nptr listUnion(nptr head1, nptr head2)
{
    nptr head3 = NULL;;
    
    nptr temp = head1;
    while(temp)
    {
        insertRear(head3, temp -> data);
        temp = temp -> next;
    }

    temp = head2;
    while(temp)
    {
        if (elementFound(head3, temp -> data) == 0) 
            insertRear(head3, temp -> data);

        temp = temp -> next;
    }

    return head3;
}

int main()
{
    nptr head1 = NULL, head2 = NULL, head3 = NULL;
    int ele;

    printf("Elements in list 1: \n");
    while(1)
    {
        scanf("%d", &ele);
        
        if(ele == -1)
            break;
        
        insertRear(head1, ele);
    } 

    display(head1);

    printf("Elements in list 2: \n");
    while(1)
    {
        scanf("%d", &ele);
        
        if(ele == -1)
            break;
        
        insertRear(head2, ele);
    } 

    display(head2);  
    
    printf("\nUnion: \n");
    display(head3 = listUnion(head1, head2));
}
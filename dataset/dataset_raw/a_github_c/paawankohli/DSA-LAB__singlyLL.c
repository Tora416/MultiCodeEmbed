#include <stdio.h>
#include <stdlib.h>

typedef struct node* nptr;
typedef struct node
{
    nptr next;
    int data;
}node;

nptr reverse(nptr head)
{
    if (head -> next == NULL)
        return head; 

    nptr newList = reverse(head -> next);
    head -> next = NULL;

    nptr temp = newList;

    while(temp -> next != NULL)
        temp = temp -> next;

    temp -> next = head;

    return newList;
}

nptr reverse2(nptr head)
{
    if(head -> next == NULL)
        return head;

    nptr prev = NULL; 
    nptr curr = head;
    nptr after = head -> next;


    while(curr)
    {
        after = curr -> next;
        curr -> next = prev;
        
        prev = curr;
        curr = after;
    }

    return prev;
}

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

int deleteFront(nptr &head)
{
    if (head == NULL)
        return -1;

    nptr temp = head;
    head = head -> next;

    int x = temp -> data;
    free(temp);
    return x;
}

int deleteRear(nptr &head)
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

    rear2 -> next = rear2 -> next -> next;
    int x = rear -> data;

    free(rear);
    return x;
}

void display(nptr &head)
{
    nptr temp = head;

    while(temp != NULL)
    {
        printf("%d --> ", temp -> data);
        temp = temp -> next;
    }

    printf("NULL\n");
}

int main()
{
    printf("1. Insert Front   2. Insert Rear   3. Delete Front   4. Delete Rear   5. Display   6. Reverse 7. Reverse2   0. Exit\n");
    int ch, ele;

    nptr head = NULL;

    do
    {
        printf("Command: "); scanf("%d", &ch);

        switch(ch)
        {
            case 1:     
                    printf("Element: "); scanf("%d", &ele);
                    insertFront(head, ele);
                    break;

            case 2:
                    printf("Element: "); scanf("%d", &ele);
                    insertRear(head, ele);
                    break;
            
            case 3: ele = deleteFront(head);
                    
                    if(ele == -1)
                        printf("List empty!\n");
                    else
                        printf("%d removed\n", ele);
                        
                    break;

            case 4: ele = deleteRear(head);
                    
                    if(ele == -1)
                        printf("List empty!\n");
                    else
                        printf("%d removed\n", ele);
                        
                    break;

            case 5: display(head);
                    break;

            case 6: head = reverse(head);
                    break; 
            
            case 7: head = reverse2(head);
                    break;
        }

    }while(ch != 0);
}
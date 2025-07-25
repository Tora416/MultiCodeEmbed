

#include<stdio.h>
#include<stdlib.h>

struct node
{
    int data;
    struct node *next;
};

typedef struct node NODE;
typedef struct node * PNODE;
typedef struct node ** PPNODE;

void InsertFirst(PPNODE Head, PPNODE Tail, int value)
{
    PNODE newn = NULL;
    newn = (PNODE)malloc(sizeof(NODE));
    newn->data = value;
    newn->next = NULL;

    if((*Head == NULL) && (*Tail == NULL))
    {
        *Head = newn;
        *Tail = newn;
    }
    else
    {
        newn->next = *Head;
        *Head = newn;
    }
    (*Tail)->next = *Head;
}

void InsertLast(PPNODE Head, PPNODE Tail, int value)
{
    PNODE newn = NULL;
    newn = (PNODE)malloc(sizeof(NODE));
    newn->data = value;
    newn->next = NULL;

    if((*Head == NULL) && (*Tail == NULL))
    {
        *Head = newn;
        *Tail = newn;
    }
    else
    {
        (*Tail)->next = newn;
        *Tail = newn;
    }
    (*Tail)->next = *Head;
}

void Display(PNODE Head, PNODE Tail)
{
    if((Head == NULL) && (Tail == NULL))
    {
        return;
    }

    do
    {
        printf("|%d|<->",Head->data);
        Head = Head->next;
    }while(Head!= Tail->next);
    printf("\n");
}

int Count(PNODE Head, PNODE Tail)
{
    int iCnt = 0;

    if((Head == NULL) && (Tail == NULL))
    {
        return 0;
    }

    do
    {
        iCnt++;
        Head = Head->next;
    }while(Head!= Tail->next);

    return iCnt;
}

void DeleteFirst(PPNODE Head, PPNODE Tail)
{
    if((*Head == NULL) && (*Tail == NULL))
    {
        return;
    }
    if(*Head == *Tail)
    {
        free(*Head);
        *Head = NULL;
        *Tail = NULL;
        return;
    }
    else
    {
        *Head = (*Head)->next;
        free((*Tail)->next);
        (*Tail)->next = *Head;
    }
}

void DeleteLast(PPNODE Head, PPNODE Tail)
{
    PNODE temp = *Head;

    if((*Head == NULL) && (*Tail == NULL))
    {
        return;
    }
    if(*Head == *Tail)
    {
        free(*Head);
        *Head = NULL;
        *Tail = NULL;
        return;
    }
    else
    {
        while(temp->next != *Tail)
        {
            temp = temp->next;
        }

        free(*Tail);
        *Tail = temp;
        (*Tail)->next = *Head;
    }
}

void InsertAtPos(PPNODE Head, PPNODE Tail, int value, int pos)
{
    int iCnt = 0, i = 0;
    PNODE temp = *Head;
    PNODE newn = NULL;

    iCnt = Count(*Head, *Tail);

    if((pos < 1) || (pos > iCnt+1))
    {
        return;
    }

    if(pos == 1)
    {
        InsertFirst(Head, Tail, value);
    }
    else if(pos == iCnt +1)
    {
        InsertLast(Head,Tail, value);
    }
    else
    {
        for(i = 1; i<pos-1;i++)
        {
            temp = temp->next;
        }
        newn = (PNODE)malloc(sizeof(NODE));
        newn->data = value;
        newn->next = NULL;

        newn->next = temp->next;
        temp->next = newn;
    }
}

void DeleteAtPos(PPNODE Head, PPNODE Tail,int pos)
{
    PNODE temp1 = *Head;
    PNODE temp2 = NULL;
    int iCnt = 0, i = 0;

    iCnt = Count(*Head,*Tail);

    if((pos < 1) || (pos > iCnt))
    {
        return;
    }
    if(pos == 1)
    {
        DeleteFirst(Head, Tail);
    }
    else if(pos == iCnt)
    {
        DeleteLast(Head, Tail);
    }
    else
    {
        for(i = 1; i< pos-1; i++)
        {
            temp1 = temp1->next;
        }

        temp2 = temp1->next;
        temp1->next = temp2->next;
        free(temp2);
    }
}

int main()
{
    PNODE First = NULL;
    PNODE Last = NULL;

    int choice = 1, no = 0, pos = 0;

    printf("-----------------------------\n");
    printf("Singly Circular Linked List\n");
    printf("-----------------------------\n");

    while(choice!= 0)   
    {
        printf("-----------------------------\n");
        printf("Enter your choice : \n");
        printf("1: Inser first\n2: Insert Last\n3: Insert at position \n4: Delete first: \n5: Delete Last\n");
        printf("6: Delete at position \n7: Display \n8: Count: \n0: Exit\n");
        scanf("%d", &choice);
        printf("-----------------------------\n");

        switch(choice)
        {
            case 1:
                printf("Enter number : \n");
                scanf("%d",&no);
                InsertFirst(&First, &Last,no);
                break;

            case 2:
                printf("Enter number : \n");
                scanf("%d",&no);
                InsertLast(&First, &Last,no);
                break;

            case 3 :
                printf("Enter number : \n");
                scanf("%d",&no);
                printf("Enter position : \n");
                scanf("%d",&pos);
                InsertAtPos(&First, &Last,no,pos);
                break;

            case 4:
                DeleteFirst(&First, &Last);
                break;

            case 5 :
                DeleteLast(&First,&Last);
                break;

            case 6:
                 printf("Enter position : \n");
                 scanf("%d",&pos);
                 DeleteAtPos(&First, &Last,pos);
                 break;

            case 7:
                Display(First, Last);
                break;

            case 8:
                printf("Number of node are %d\n", Count(First, Last));
                break;

            case 0:
                printf("Thank you for using the application...\n");
                break;

            default:
                printf("Error : Wrong choice..\n");
        }
    }

    return 0;
}


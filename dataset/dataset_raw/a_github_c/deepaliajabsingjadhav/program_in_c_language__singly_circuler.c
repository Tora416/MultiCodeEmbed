

#include<stdio.h>
#include<stdlib.h>

struct Node
{
    int data;
    struct Node *next;
    struct Node *prev;
};

typedef struct Node NODE;
typedef struct Node * PNODE;
typedef struct Node ** PPNODE;

void InsertLast(PPNODE Head, PPNODE Tail, int value)
{
    PNODE newn = NULL;
    
    newn = (PNODE)malloc(sizeof(NODE));
    
    newn->data = value;
    newn->next = NULL;
    newn->prev = NULL;
    
    if((*Head ==NULL) && (*Tail == NULL))       
    {
        *Head = newn;
        *Tail = newn;
    }
    else            
    {
        (*Tail)->next = newn;
        newn->prev = *Tail;
        *Tail = (*Tail) ->next;   
    }
    (*Tail)->next = *Head;
    (*Head)->prev = *Tail;
}

void InsertFirst(PPNODE Head, PPNODE Tail, int value)
{
    PNODE newn = NULL;
    
    newn = (PNODE)malloc(sizeof(NODE));
    
    newn->data = value;
    newn->next = NULL;
    newn->prev = NULL;
    
    if((*Head ==NULL) && (*Tail == NULL))       
    {
        *Head = newn;
        *Tail = newn;
    }
    else            
    {
        newn->next = *Head;
        (*Head)->prev = newn;
        *Head = (*Head)->prev;
    }
    (*Tail)->next = *Head;
    (*Head)->prev = *Tail;
}

void Display(PNODE Head, PNODE Tail)
{
        if((Head == NULL) && (Tail == NULL))
        {
            return;
        }
        do
        {
            printf("|%d| <-> ",Head->data);
            Head = Head->next;
        }while(Head != Tail->next);
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
        }while(Head != Tail->next);

    return iCnt;
}

void DeleteFirst(PPNODE Head, PPNODE Tail)
{
    if(*Head == NULL && *Tail == NULL)  
    {
        return;
    }
    
    if(*Head == *Tail)  
    {
        free(*Head);
        *Head = NULL;
        *Tail = NULL;
    }
    else    
    {
        *Head = (*Head)->next;
        free((*Tail)->next);    
    
        (*Head)->prev = *Tail;
        (*Tail)->next = *Head;
    }
}

void DeleteLast(PPNODE Head, PPNODE Tail)
{
    if(*Head == NULL && *Tail == NULL)  
    {
        return;
    }
    
    if(*Head == *Tail)  
    {
        free(*Head);
        *Head = NULL;
        *Tail = NULL;
    }
    else    
    {
        *Tail  = (*Tail )->prev;
        free((*Tail)->next);      
        
        (*Head)->prev = *Tail;
        (*Tail)->next = *Head;
    }
}

void InsertAtPos(PPNODE Head, PPNODE Tail, int value, int pos)
{
    int count = 0, i= 0;
    PNODE temp = *Head;
    PNODE newn = NULL;
    
    count = Count(*Head, *Tail);
    
    if((pos < 1) || (pos > (count + 1)))
    {
        return;
    }
    if(pos == 1)
    {
        InsertFirst(Head, Tail, value);
    }
    else if(pos == count + 1)
    {
        InsertLast(Head,Tail,value);
    }
    else
    {
        newn= (PNODE)malloc(sizeof(NODE));
        
        newn->next = NULL;
        newn->prev = NULL;
        newn->data = value;
        
        for(i = 1; i< pos-1; i++)
        {
            temp = temp->next;
        }
        
        newn->next = temp->next;
        temp->next->prev = newn;
        
        temp->next = newn;
        newn->prev = temp;
    }
}

void DeleteAtPos(PPNODE Head,PPNODE Tail, int pos)
{
    int cnt = 0,i = 0;
    PNODE temp = *Head;
    
    cnt = Count(*Head, *Tail);
    
    if((pos < 1) || (pos > cnt))
    {
        return;
    }
    if(pos == 1)
    {
        DeleteFirst(Head, Tail);
    }
    else if(pos == cnt)
    {
        DeleteLast(Head, Tail);
    }
    else
    {
        for(i = 1; i<pos-1; i++)
        {
            temp =temp->next;
        }
        temp->next = temp->next->next;
        free(temp->next->prev);
        temp->next->prev = temp;
    }
}
int main()
{
    PNODE First = NULL;
    PNODE Last = NULL;          
    int no = 0, iRet = 0;
    
    printf("Enter number : ");
    scanf("%d",&no);
    InsertFirst(&First,&Last,no);
    
    printf("Enter number : ");
    scanf("%d",&no);
    InsertFirst(&First,&Last,no);
    
    printf("Enter number : ");
    scanf("%d",&no);
    InsertFirst(&First,&Last,no);
    
    printf("Enter number : ");
    scanf("%d",&no);
    InsertFirst(&First,&Last,no);
    
    printf("Contents of linked lista are \n");
    Display(First, Last);
    
    iRet = Count(First,Last);
    
    printf("\nNumber of lements are %d\n",iRet);
    
    DeleteLast(&First,&Last);
    DeleteFirst(&First,&Last);
    
    printf("Contents of linked lista are \n");
    Display(First, Last);
    
        return 0;
}

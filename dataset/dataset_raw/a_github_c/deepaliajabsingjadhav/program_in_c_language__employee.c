#include<stdio.h>
#include<stdlib.h>

typedef struct Employee
{
    int Eno;
    char EName[20];
    struct Employee *next;
}NODE, *PNODE,**PPNODE;

void InsertFirst(PPNODE Head)
{
    PNODE newn = (PNODE)malloc(sizeof(NODE));
    printf("Enter employee ID\n");
    scanf("%d",&(newn->Eno));
    
    printf("Enter name\n");
    scanf(" %[^'\n']s",newn->EName);
    
    if(*Head == NULL)
    {
        *Head = newn;
    }
    else
    {
        newn->next = *Head;
        *Head = newn;
    }
}

void Display(PNODE Head)
{
    while(Head != NULL)
    {
        printf("Emplyee number : %d\t Name : %s\n",Head->Eno, Head->EName);
        Head = Head->next;
    }
}

int main()
{
    PNODE First = NULL;
    
    InsertFirst(&First);
        InsertFirst(&First);
        InsertFirst(&First);
    
    printf("Information of Employess\n");
    
    Display(First);
    
    return 0;
}

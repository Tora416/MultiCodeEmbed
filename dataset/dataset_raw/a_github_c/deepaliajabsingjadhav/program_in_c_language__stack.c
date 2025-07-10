







#include<stdio.h>
#include<stdlib.h>

struct node
{
    int data;
    struct node *next;
};

typedef struct node NODE;
typedef struct node * PNODE;
typedef  struct node ** PPNODE;

void Push(PPNODE Head, int value)   
{
    PNODE newn = (PNODE) malloc(sizeof(NODE));
    newn->data = value;
    newn->next = NULL;
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
int Pop(PPNODE Head)        
{
    int no = 0;
    PNODE temp = *Head;
    
    if(*Head == NULL)
    {
        printf("Stack is empty\n");
        return -1;
    }
    else
    {
        no = (*Head)->data;         
        *Head = (*Head)->next;
        free(temp);
        return no;
    }
}

int Peep(PNODE Head)    
{
    int no = 0;
    
    if(Head == NULL)
    {
        printf("Stack is empty\n");
        return -1;
    }
    else
    {
        no = Head->data;
        return no;
    }
}

void Display(PNODE Head)    
{
    while(Head != NULL)
    {
        printf("|%d|->",Head->data);
        Head = Head->next;
    }
    printf("\n");
}

int Count(PNODE Head)       
{
    int iCnt = 0;
    
    while(Head != NULL)
    {
        iCnt++;
        Head = Head->next;
    }
    return iCnt;
}

int main()
{
    PNODE First = NULL;
    int choice = 1, no = 0;
    
    printf("Dynamic implementation of stack\n");
    
    while(choice != 0)
    {
        printf("\n 1: Push the element");
        printf("\n 2: Pop the elemet");
        printf("\n 3: Display the elemets of stack");
        printf("\n 4: Count the number of elements of stack");
        printf("\n 5: Peep the element");
        printf("\n 0: Exit the application\n");
        
        printf("Please enter your choice : \n");
        scanf("%d",&choice);
        
        switch (choice)
        {
            case 1:
                printf("Enter the element that you want to insert\n");
                scanf("%d",&no);
                Push(&First, no);
                break;
                
            case 2 :
                no = Pop(&First);
                printf("Poped element is : %d\n",no);
                break;
              
            case 3 :
                Display(First);
                break;
                
            case 4:
                printf("Number of elements are : %d\n",Count(First));
                break;
                
            case 5:
                printf("Peeped element is : %d\n",Peep(First));
                break;
                
            case 0:
                printf("Thank you for using the application\n");
                break;
                
            default:
                printf("Wrong choice\n");
        } 
    }
    
    return 0;
}









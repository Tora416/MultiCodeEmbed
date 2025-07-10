
#include<stdio.h>
#include<stdlib.h>
typedef struct s
{
    int data;
    struct s* next;
}node;
node* createNode()
{
    node* newnode=malloc(sizeof(node));
    newnode->data=0;
    newnode->next=NULL;
    return newnode;
}
void push(node** head, int n)
{
    node* linklist=createNode();
    linklist->data=n;
    linklist->next=*head;
    *head=linklist;
    printf("%d pushed to stack\n",n);
}
int isempty(node* head)
{
    if(head==NULL)
        return 1;
    else
        return 0;
}
void pop(node** head)
{
    if(isempty(*head))
        printf("STACK EMPTY\n");
    else
    {
        node* temp=*head;
        *head=(*head)->next;
        printf("%d popped from stack\n",temp->data);
        free(temp);
    }
}
int main()
{
    int ch;
    node* head=NULL;
    while(1)
    {
        printf("\n");
        printf("1. PUSH\n");
        printf("2. POP\n");
        printf("3. EXIT\n");
        printf("Enter your choice: ");
        scanf("%d",&ch);
        if (ch==1)
        {
            int n;
            scanf("%d",&n);
            push(&head,n);
        }
        else if (ch==2)
            pop(&head);
        else if (ch==3)
        {
            printf("Exitting program, Thank you.\n");
            break;
        }
        else
            printf("Invalid, choice try again.\n");
    }
    return 0;
}
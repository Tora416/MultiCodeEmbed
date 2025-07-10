#include<stdio.h>
#include<stdlib.h>
typedef struct a
{
    int data;
    struct a* next;
}node;
node* createnode(int inp)
{
    node* newnode=malloc(sizeof(node));
    newnode->data=inp;
    newnode->next=NULL;
    return newnode;
}
void insert(node** head, int inp)
{
    node* linklist=createnode(inp);
    linklist->next=*head;
    *head=linklist;
    printf("%d inserted\n",(*head)->data);
}
void removeeven(node** head)
{
    while((*head)!=NULL && (*head)->data%2==0)
        *head=(*head)->next;
    node* h=*head;
    if((*head)==NULL)
        return;
    while(h->next!=NULL)
    {
        if(h->next->data%2==0)
            h->next=h->next->next;
        else
            h=h->next;
    }
}
void print(node** head)
{
    if(*head==NULL)
        printf("\nSTACK EMPTY\n");
    else
    {
        node* h=*head;
        printf("\n LINK-LIST:");
        while(h!=NULL)
        {
            printf("  %d",h->data);
            h=h->next;
        }
        printf("\n");
    }
}
int main()
{
    int n;
    node* head=NULL;
    while(1)
    {
        printf("\n1. INSERT\n");
        printf("2. REMOVE EVEN\n");
        printf("3. PRINT\n");
        printf("4. EXIT\n");
        printf("Enter choice: ");
        scanf("%d",&n);
        if(n==1)
        {
            int inp;
            printf("Enter the element: ");
            scanf("%d",&inp);
            insert(&head,inp);
        }
        else if(n==2)
        {
            removeeven(&head);
            printf("All even integers removed.\n");
        }
        else if(n==3)
            print(&head);
        else if(n==4)
        {
            printf("Exitting program, Thank you.\n");
            break;
        }
        else
            printf("INVALID CHOICE, TRY AGAIN!\n");
    }
    return 0;
}
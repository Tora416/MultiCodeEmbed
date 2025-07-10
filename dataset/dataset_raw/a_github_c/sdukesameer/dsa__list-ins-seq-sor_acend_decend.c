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
void sequential_insert(node** head, int inp)
{
    node* linklist=createnode(inp);
    linklist->next=*head;
    *head=linklist;
    printf("%d inserted\n",(*head)->data);
}
void sorted_insert_asc(node** head, int inp)
{
    node* newnode=createnode(inp);
    if(*head==NULL||newnode->data < (*head)->data)
    {
        newnode->next=*head;
        *head=newnode;
        printf("%d inserted\n",(*head)->data);
    }
    else
    {
        node* temp=*head;
        while(temp->next!=NULL&&temp->next->data < newnode->data)
            temp=temp->next;
        newnode->next=temp->next;
        temp->next=newnode;
        printf("%d inserted\n",temp->next->data);
    }
}
void sorted_insert_dec(node** head, int inp)
{
    node* newnode=createnode(inp);
    if(*head==NULL||newnode->data > (*head)->data)
    {
        newnode->next=*head;
        *head=newnode;
        printf("%d inserted\n",(*head)->data);
    }
    else
    {
        node* temp=*head;
        while(temp->next!=NULL&&temp->next->data > newnode->data)
            temp=temp->next;
        newnode->next=temp->next;
        temp->next=newnode;
        printf("%d inserted\n",temp->next->data);
    }
}
void print(node** head)
{
    if(*head==NULL)
        printf("STACK EMPTY\n");
    else
    {
        node* h=*head;
        printf("      STACK      \n");
        while(h!=NULL)
        {
            printf("\t%d\n",h->data);
            h=h->next;
        }
    }
}
int main()
{
    int ch;
    while(1)
    {
        printf("\n1. SORTED ORDER\n");
        printf("2. SEQUENTIAL ORDER\n");
        printf("3. EXIT PROGRAM\n");
        printf("Enter your choice: ");
        scanf("%d",&ch);
        if (ch==1)
        {
            int x;
            while(1)
            {
                printf("\n1. ASCENDING ORDER\n");
                printf("2. DESCENDING ORDER\n");
                printf("3. EXIT\n");
                printf("Enter choice: ");
                scanf("%d",&x);
                if(x==1)
                {
                    int n;
                    node* head=NULL;
                    printf("\n\t ASCENDING ORDER\n");
                    while(1)
                    {
                        printf("\n1. INSERT\n");
                        printf("2. PRINT\n");
                        printf("3. EXIT\n");
                        printf("Enter choice: ");
                        scanf("%d",&n);
                        if (n==1)
                        {
                            int inp;
                            printf("Enter the element: ");
                            scanf("%d",&inp);
                            sorted_insert_asc(&head,inp);;
                        }
                        else if (n==2)
                        {
                            print(&head);
                        }
                        else if (n==3)
                        {
                            printf("Exitting, Thank you.\n");
                            break;
                        }
                        else
                            printf("INVALID CHOICE, TRY AGAIN\n");
                    }
                }
                else if(x==2)
                {
                    int n;
                    node* head=NULL;
                    printf("\n\t DESCENDING ORDER\n");
                    while(1)
                    {
                        printf("\n1. INSERT\n");
                        printf("2. PRINT\n");
                        printf("3. EXIT\n");
                        printf("Enter choice: ");
                        scanf("%d",&n);
                        if (n==1)
                        {
                            int inp;
                            printf("Enter the element: ");
                            scanf("%d",&inp);
                            sorted_insert_dec(&head,inp);;
                        }
                        else if (n==2)
                        {
                            print(&head);
                        }
                        else if (n==3)
                        {
                            printf("Exitting, Thank you.\n");
                            break;
                        }
                        else
                            printf("INVALID CHOICE, TRY AGAIN\n");
                    }
                }
                else if(x==3)
                {
                    printf("Exitting, Thank you.\n");
                    break;
                }
                else
                {
                    printf("INVALID CHOICE, TRY AGAIN\n");
                }
            }
        }
        else if(ch==2)
        {
            int n;
            node* head=NULL;
            while(1)
            {
                printf("\n1. INSERT\n");
                printf("2. PRINT\n");
                printf("3. EXIT\n");
                printf("Enter choice: ");
                scanf("%d",&n);
                if(n==1)
                {
                    int inp;
                    printf("Enter the element: ");
                    scanf("%d",&inp);
                    sequential_insert(&head,inp);
                }
                else if(n==2)
                    print(&head);
                else if(n==3)
                {
                    printf("Exitting, Thank you.\n");
                    break;
                }
                else
                    printf("INVALID CHOICE, TRY AGAIN!\n");
            }
        }
        else if(ch==3)
        {
            printf("Exitting program, Thank you.\n");
                break;
        }
        else
            printf("SORRY, INVALID CHOICE, TRY AGAIN!\n");
    }
    return 0;
}
#include<stdio.h>
#include<stdlib.h>
typedef struct n
{ 
    int key;
    struct n *prev, *next; 
}list;
void sort_insertion(list** head, int n)
{
    list* node=(list*)malloc(sizeof(list));
    node->key=n;
    node->next=NULL;
    node->prev=NULL;
    if(*head==NULL)
        *head=node;
    else if(node->key <= (*head)->key)
    {
        (*head)->prev=node;
        node->next=*head;
        *head=node;
    }
    else
    {
        list* temp=*head;
        while(temp->next != NULL && temp->next->key < node->key)
            temp=temp->next;
        node->prev=temp;
        node->next=temp->next;
        temp->next=node;
        if(node->next!=NULL)
            node->next->prev=node;
    }
}
void seq_insertion(list** head, int n)
{
    list* dll=(list*)malloc(sizeof(list));
    dll->key=n;
    dll->next=*head;
    dll->prev=NULL;
    if (*head!=NULL)
        (*head)->prev=dll;
    *head=dll;
}
list* search_node(list* head, int n) 
{
    list* dll=head;
    while (dll!=NULL)
    {
        if(dll->key==n)
            return dll;
        dll=dll->next;
    }
    return NULL;
}
void deletion(list** head, list* del)
{
    if (*head==del)
        *head=del->next;
    else 
    {
        if (del->next!=NULL)
            del->next->prev=del->prev;
        if (del->prev!=NULL)
            del->prev->next=del->next;
    }
    free(del);
}
void printfwd(list* head)
{
    list* dll=head;
    while (dll!=NULL)
    {
        printf("%d  ",dll->key);
        dll=dll->next;
    }
}
void printrev(list* head)
{
    list* dll=head;
    while (dll->next!=NULL)
        dll=dll->next;
    while(dll!=NULL)
    {
        printf("%d  ",dll->key);
        dll=dll->prev;
    }
}
int main()
{
    while (1)
    {
        int ch;
        printf("\n1. SORTED ORDER INSERTION\n");
        printf("2. SEQUENTIAL ORDER INSERTION\n");
        printf("3. EXIT PROGRAM\n");
        printf("Enter your choice: ");
        scanf("%d",&ch);
        if(ch==1)
        {
            list* head=NULL;
            int c;
            while(1)
            {
                int c;
                printf("\n1. ENTER AN INTEGER\n");
                printf("2. DELETE AN INTEGER\n");
                printf("3. TRAVERSAL IN FORWARD DIRECTION\n");
                printf("4. TRAVERSAL IN REVERSE DIRECTION\n");
                printf("5. EXIT SORTED ORDER INSERTION\n");
                printf("Enter your choice: ");
                scanf("%d",&c);
                if(c==1)
                {
                    int n;
                    printf("Please enter an element: ");
                    scanf("%d",&n);
                    sort_insertion(&head,n);
                    printf("%d inserted using SORTED ORDER INSERTION.\n",n);
                }
                else if(c==2)
                {
                    int n;
                    printf("\nPlease enter the element to be deleted: ");
                    scanf("%d",&n);
                    if (head==NULL)
                        printf("COULDN'T DELETE %d. LIST IS EMPTY\n",n);
                    else
                    {
                        list* del_node=search_node(head,n);
                        if(del_node==NULL)
                        printf("COULDN'T DELETE %d. NOT FOUND IN LIST.\n",n);
                        else
                        {
                            deletion(&head,del_node);
                            printf("%d deleted from LIST.\n",n);
                        }
                    }
                }
                else if (c==3)
                {
                    if(head==NULL)
                        printf("\n\tLIST IS EMPTY\n");
                    else
                    {
                        printf("\nTRAVERSAL IN FORWARD DIRECTION: \n");
                        printfwd(head);
                        printf("\n");
                    }
                }
                else if (c==4)
                {
                    if(head==NULL)
                        printf("\n\tLIST IS EMPTY\n");
                    else
                    {
                        printf("\nTRAVERSAL IN REVERSE DIRECTION: \n");
                        printrev(head);
                        printf("\n");
                    }
                }
                else if (c==5)
                {
                    printf("\nExitting Sorted Order Insertion, Thank You.\n");
                    break;
                }
                else
                    printf("\nINVALID CHOICE! TRY AGAIN.\n");
            }
        }
        else if(ch==2)
        {
            list* head=NULL;
            int c;
            while(1)
            {
                printf("\n1. ENTER AN INTEGER\n");
                printf("2. DELETE AN INTEGER\n");
                printf("3. TRAVERSAL IN FORWARD DIRECTION\n");
                printf("4. TRAVERSAL IN REVERSE DIRECTION\n");
                printf("5. EXIT SORTED ORDER INSERTION\n");
                printf("Enter your choice: ");
                scanf("%d",&c);
                if(c==1)
                {
                    int n;
                    printf("Please enter an element: ");
                    scanf("%d",&n);
                    seq_insertion(&head,n);
                    printf("%d inserted using SEQUENTIAL ORDER INSERTION.\n",n);
                }
                else if(c==2)
                {
                    int n;
                    printf("\nPlease enter the element to be deleted: ");
                    scanf("%d",&n);
                    if (head==NULL)
                        printf("COULDN'T DELETE %d. LIST IS EMPTY\n",n);
                    else
                    {
                        list* del_node=search_node(head,n);
                        if(del_node==NULL)
                        printf("COULDN'T DELETE %d. NOT FOUND IN LIST.\n",n);
                        else
                        {
                            deletion(&head,del_node);
                            printf("%d deleted from LIST.\n",n);
                        }
                    }
                }
                else if (c==3)
                {
                    if(head==NULL)
                        printf("\n\tLIST IS EMPTY\n");
                    else
                    {
                        printf("\nTRAVERSAL IN FORWARD DIRECTION: \n");
                        printfwd(head);
                        printf("\n");
                    }
                }
                else if (c==4)
                {
                    if(head==NULL)
                        printf("\n\tLIST IS EMPTY\n");
                    else
                    {
                        printf("\nTRAVERSAL IN REVERSE DIRECTION: \n");
                        printrev(head);
                        printf("\n");
                    }
                }
                else if(c==5)
                {
                    printf("\nExitting Sorted Order Insertion, Thank You.\n");
                    break;
                }
                else
                    printf("\nINVALID CHOICE! TRY AGAIN.\n");
            }
        }
        else if(ch==3)
        {
            printf("\nExitting Program, Thank You.\n");
            break;
        }
        else
            printf("\nINVALID CHOICE! TRY AGAIN.\n");
    }
    return 0;
}
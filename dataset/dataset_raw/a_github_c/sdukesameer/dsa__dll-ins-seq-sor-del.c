
#include<stdio.h>
#include<stdlib.h>
typedef struct x
{
    struct x* prev;
    int data;
    struct x* next;
}node;
void sort_insertion(node** head, int n)
{
    node* dll=(node*)malloc(sizeof(node));
    dll->data=n;
    dll->next=NULL;
    dll->prev=NULL;
    if(*head==NULL)
        *head=dll;
    else if(dll->data <= (*head)->data)
    {
        (*head)->prev=dll;
        dll->next=*head;
        *head=dll;
    }
    else
    {
        node* temp=*head;
        while(temp->next != NULL && temp->next->data < dll->data)
            temp=temp->next;
        dll->prev=temp;
        dll->next=temp->next;
        temp->next=dll;
        if(dll->next!=NULL)
            dll->next->prev=dll;
    }
}
void seq_insertion(node** head, int n)
{
    node* dll=(node*)malloc(sizeof(node));
    dll->data=n;
    dll->next=*head;
    dll->prev=NULL;
    if (*head!=NULL)
        (*head)->prev=dll;
    *head=dll;
}
node* search_node(node* head, int n) 
{
    node* dll=head;
    while (dll!=NULL)
    {
        if(dll->data==n)
            return dll;
        dll=dll->next;
    }
    return NULL;
}
void deletion(node** head, node* del)
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
void printforward(node* head)
{
    node* dll=head;
    while (dll!=NULL)
    {
        printf("%d  ",dll->data);
        dll=dll->next;
    }
}
void printreversed(node* head)
{
    node* dll=head;
    while (dll->next!=NULL)
        dll=dll->next;
    while(dll!=NULL)
    {
        printf("%d  ",dll->data);
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
            printf("\n\tSORTED ORDER\n");
            node* head=NULL;
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
                        printf("COULDN'T DELETE %d. LIST EMPTY\n",n);
                    else
                    {
                        node* del_node=search_node(head,n);
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
                        printf("\n\tLIST EMPTY\n");
                    else
                    {
                        printf("\nTRAVERSAL IN FORWARD DIRECTION: \n");
                        printforward(head);
                        printf("\n");
                    }
                }
                else if (c==4)
                {
                    if(head==NULL)
                        printf("\n\tLIST EMPTY\n");
                    else
                    {
                        printf("\nTRAVERSAL IN REVERSE DIRECTION: \n");
                        printreversed(head);
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
            printf("\n\tSEQUENTIAL ORDER\n");
            node* head=NULL;
            int c;
            while(1)
            {
                printf("\n1. ENTER AN INTEGER\n");
                printf("2. DELETE AN INTEGER\n");
                printf("3. TRAVERSAL IN FORWARD DIRECTION\n");
                printf("4. TRAVERSAL IN REVERSE DIRECTION\n");
                printf("5. EXIT SEQUENTIAL ORDER INSERTION\n");
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
                        printf("COULDN'T DELETE %d. LIST EMPTY\n",n);
                    else
                    {
                        node* del_node=search_node(head,n);
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
                        printf("\n\tLIST EMPTY\n");
                    else
                    {
                        printf("\nTRAVERSAL IN FORWARD DIRECTION: \n");
                        printforward(head);
                        printf("\n");
                    }
                }
                else if (c==4)
                {
                    if(head==NULL)
                        printf("\n\tLIST EMPTY\n");
                    else
                    {
                        printf("\nTRAVERSAL IN REVERSE DIRECTION: \n");
                        printreversed(head);
                        printf("\n");
                    }
                }
                else if(c==5)
                {
                    printf("\nExitting Sequential Order Insertion, Thank You.\n");
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

#include<stdio.h>
#include<stdlib.h>
typedef struct x
{
    int data;
    struct x* next;
}node;
node* createNode(int n)
{
    node* newNode=(node*)malloc(sizeof(node));
    newNode->data=n;
    newNode->next=NULL;
    return newNode;
}
void sort_insertion(node** head, int n)
{
    node* cll=createNode(n);
    if (*head==NULL)
    {
        *head=cll;
        cll->next=cll;
    }
    else if((*head)->data >= cll->data)
    {
        node* last=*head;
        while(last->next!=(*head))
            last=last->next;
        cll->next=*head;
        last->next=cll;
        *head=cll;
    }
    else if((*head)->data < cll->data)
    {
        node* temp=*head;
        while(temp->next!=*head && temp->next->data<cll->data)
            temp=temp->next;
        cll->next=temp->next;
        temp->next=cll;
    }
}
void seq_insertion(node** head, int n)
{
    node* cll=createNode(n);
    if(*head==NULL)
    {
        *head=cll;
        cll->next=cll;
    }
    else
    {
        cll->next=*head;
        node* last=*head;
        while(last->next!=(*head))
            last=last->next;
        last->next=cll;
        *head=cll;
    }
}
node* search(node* head, int n)
{
    node* cll=head;
    do
    {
        if(cll->data==n)
            return cll;
        cll=cll->next;
    }
    while(cll!=head);
    return NULL;
}
void deletion(node** head, node* del)
{
    if (*head==del)
    {
        if((*head)->next==*head)
            *head=NULL;
        else
        {
            node* last=*head;
            while(last->next!=(*head))
                last=last->next;
            *head=(*head)->next;
            last->next=*head;
        }
    }
    else
    {
        node* temp=*head;
        while(temp->next!=del)
            temp=temp->next;
        temp->next=del->next;
    }
    free(del);
}
void print(node* head)
{
    node* temp=head;
    do
    {
        printf("%d ",temp->data);
        temp=temp->next;
    }
    while(temp!=head);
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
                printf("3. DISPLAY CONTENT OF CIRCULAR LINK-LIST\n");
                printf("4. EXIT SORTED ORDER INSERTION\n");
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
                    if (head==NULL)
                        printf("\nCAN'T DELETE. LIST EMPTY\n");
                    else
                    {
                        int n;
                        printf("\nPlease enter the element to be deleted: ");
                        scanf("%d",&n);
                        node* del_node=search(head,n);
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
                        printf("\nDISPLAYING CONTENTS OF CIRCULAR LINK-LIST: \n");
                        print(head);
                        printf("\n");
                    }
                }
                else if (c==4)
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
                int c;
                printf("\n1. ENTER AN INTEGER\n");
                printf("2. DELETE AN INTEGER\n");
                printf("3. DISPLAY CONTENT OF CIRCULAR LINK-LIST\n");
                printf("4. EXIT SEQUENTAIL ORDER INSERTION\n");
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
                    if (head==NULL)
                        printf("\nCAN'T DELETE. LIST EMPTY\n");
                    else
                    {
                        int n;
                        printf("\nPlease enter the element to be deleted: ");
                        scanf("%d",&n);
                        node* del_node=search(head,n);
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
                        printf("\nDISPLAYING CONTENTS OF CIRCULAR LINK-LIST: \n");
                        print(head);
                        printf("\n");
                    }
                }
                else if (c==4)
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
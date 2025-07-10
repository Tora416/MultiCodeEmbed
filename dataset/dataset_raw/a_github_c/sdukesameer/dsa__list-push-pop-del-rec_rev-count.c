#include<stdio.h>
#include<stdlib.h>
typedef struct s
{
    int data;
    struct s* next;
}node;
node* createNode(node* head, int n)
{
    node* newnode=malloc(sizeof(node));
    newnode->data=n;
    newnode->next=head;
    return newnode;
}
node* push(node* head, int data)
{
    if(head==NULL)
        return createNode(head,data);
    else
        head->next=push(head->next,data);
    return head;
}
node* pop(node* head)
{
    if(head==NULL)
        printf("CAN'T POP, STACK EMPTY\n");
    else if(head->next==NULL)
    {
        printf("%d popped from stack\n",head->data);
        free(head);
        return NULL;
    }
    else
    {
        head->next=pop(head->next);
        return head;
    }
}
void delete(node** head, int key)
{
    if(*head==NULL)
        printf("CAN'T DELETE, STACK EMPTY\n");
    else
    {
        int c=0,f=0;
        node* prev;
        node* cur=*head;
        while(cur != NULL)
        {
            c++;
            if(c==1)
            {    if (cur->data==key)
                {
                    *head=cur->next;
                    free(cur);
                    cur=*head;
                    f=1;c=0;
                }
                else
                {
                    prev=cur;
                    cur=cur->next;
                }
            }
            else
            {
                if(cur->data==key)
                {
                    prev->next=cur->next;
                    free(cur);
                    cur=prev->next;
                    f=1;
                }
                else
                {
                    prev=cur;
                    cur=cur->next;
                }
            }
        }
        if(f==0)
            printf("NO MATCH FOUND\n");
        else
            printf("Match found!\nAll matching elements deleted successfully.\n");
    }
}
node* rec_reverse(node* head)
{
    if(head == NULL || head->next == NULL)
        return head;
    node* revHead = rec_reverse(head->next);
    head->next->next = head;
    head->next = NULL; 
    return revHead;
}
int count(node* head)
{
    if(head==NULL)
        return 0;
    else
        return count(head->next)+1;
}
node* print(node* head)
{
    if(head==NULL)
        return NULL;
    else if(head->next==NULL)
    {
        printf("      STACK      \n");
        return head;
    }
    else
    {
        printf("\t%d\n",(print(head->next))->data);
        return head;
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
        printf("3. DELETE\n");
        printf("4. REVERSE\n");
        printf("5. COUNT\n");
        printf("6. PRINT\n");
        printf("7. EXIT\n");
        printf("Enter your choice: ");
        scanf("%d",&ch);
        if (ch==1)
        {
            int n;
            printf("Enter the element: ");
            scanf("%d",&n);
            head=push(head, n);
        }
        else if (ch==2)
            head=pop(head);
        else if (ch==3)
        {
            int key;
            printf("Enter the element you want to delete: ");
            scanf("%d",&key);
            delete(&head,key);
        }
        else if (ch==4)
        {
            if(head==NULL)
                printf("CAN'T REVERSE, STACK EMPTY\n");
            else
            {
                head=rec_reverse(head);
                printf("Link-List Reversed\n");
            }
        }
        else if (ch==5)
            printf("Count of elements are= %d\n",count(head));
        else if (ch==6)
        {
            node* temp=print(head);
            if(temp==NULL)
                printf("CAN'T PRINT, STACK EMPTY\n");
            else
                printf("\t%d\n",temp->data);
        }
        else if (ch==7)
        {
            printf("Exitting program, Thank you.\n");
            break;
        }
        else
            printf("Invalid, choice try again.\n");
    }
    return 0;
}
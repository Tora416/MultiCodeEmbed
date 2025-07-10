#include <stdio.h>
#include <stdlib.h>
struct node {
    int data;
    struct node * next;
}*head;
void createList(int n);
void displayList();
void insertAtBeginning(int data);
void insertAtN(int data, int position);


int main()
{
    int n, data, choice=1;

    head = NULL;
                printf("Enter the total number of nodes in list: ");
                scanf("%d", &n);
                createList(n);
                displayList();
                printf("Enter node position: ");
                scanf("%d", &n);
                printf("Enter data you want to insert at %d position: ", n);
                scanf("%d", &data);
                insertAtN(data, n);
                displayList();


    return 0;
}
 
 
void createList(int n)
{
    int i, data;
    struct node *prevNode, *newNode;
        head = (struct node *)malloc(sizeof(struct node));

        printf("Enter data of 1 node: ");
        scanf("%d", &data);

        head->data = data;
        head->next = NULL;

        prevNode = head;
        for(i=2; i<=n; i++)
        {
            newNode = (struct node *)malloc(sizeof(struct node));

            printf("Enter data of %d node: ", i);
            scanf("%d", &data);

            newNode->data = data;
            newNode->next = NULL;

            
            prevNode->next = newNode;
            
            prevNode = newNode;
        }

        
        prevNode->next = head;
}
void displayList()
{
    struct node *current;
    int n = 1;

    if(head == NULL)
    {
        printf("List is empty.\n");
    }
    else
    {
        current = head;
        printf("DATA IN THE LIST:\n");

        do {
            printf("Data %d = %d\n", n, current->data);

            current = current->next;
            n++;
        }while(current != head);
    }
}
void insertAtBeginning(int data)
{
    struct node *newNode, *current;

    if(head == NULL)
    {
        printf("List is empty.\n");
    }
    else
    {
         
        newNode = (struct node *)malloc(sizeof(struct node));
        newNode->data = data;
        newNode->next = head;
         
        
        current = head;
        while(current->next != head)
        {
            current = current->next;
        }
        current->next = newNode;

        
        head = newNode;

        printf("NODE INSERTED SUCCESSFULLY\n");
    }
}
void insertAtN(int data, int position)
{
    struct node *newNode, *current;
    int i;

    if(head == NULL)
    {
        printf("List is empty.\n");
    }
    else if(position == 1)
    {
    
    struct node *newNode, *current;
        
        newNode = (struct node *)malloc(sizeof(struct node));
        newNode->data = data;
        newNode->next = head;
         
        current = head;
        while(current->next != head)
        {
            current = current->next;
        }
        current->next = newNode;

        
        head = newNode;
}
    else
    {
        
        newNode = (struct node *)malloc(sizeof(struct node));
        newNode->data = data;
        
        current = head;
        for(i=2; i<=position-1; i++)
        {
            current = current->next;
        }
        
        newNode->next = current->next;
        current->next = newNode;

    }
}

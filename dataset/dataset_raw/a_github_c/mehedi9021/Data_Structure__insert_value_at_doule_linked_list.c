#include <stdio.h>
#include <stdlib.h>
struct node {
    int data;
    struct node * next;
}*head;
void createList(int n);
void displayList();

void insertAtN(int data, int position);


int main()
{
    int n, data;

    head = NULL;
    printf("Enter the total number of nodes in list: ");
    scanf("%d", &n);
    createList(n);
    displayList();
    printf("Enter node position: ");
    scanf("%d", &n);
    printf("Enter data you want to insert at %d position: ", n);
    insertAtN(data, n);
    displayList();

    return 0;
}
void createList(int n)
{
    int i, data;
    struct node *prevNode, *newNode;

    if(n >= 1)
    {
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

        printf("\nCIRCULAR LINKED LIST CREATED SUCCESSFULLY\n");
    }
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
void insertAtN(int data, int position)
{
    struct node *newNode, *current;
    int i;
    if(position == 1)
    {
    struct node *newNode, *current;
    newNode = (struct node *)malloc(sizeof(struct node));
    scanf("%d", &data);
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
        scanf("%d", &data);
        newNode->data = data;
        current = head;
        for(i=2; i<=position-1; i++)
        {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;

        printf("NODE INSERTED SUCCESSFULLY.\n");
    }
}

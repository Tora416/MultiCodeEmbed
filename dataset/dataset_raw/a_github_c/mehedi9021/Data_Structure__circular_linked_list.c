#include <stdio.h>
#include <stdlib.h>
struct node {
    int data;
    struct node * next;
}*head;

void createList(int n);
void displayList();


int main()
{
    int n, data, choice=1;

    head = NULL;

    printf("Enter the total number of nodes in list: ");
    scanf("%d", &n);
    createList(n);
    displayList();

    return 0;
}
void createList(int n)
{
    int i, data;
    struct node *temp, *newNode;
        head = (struct node *)malloc(sizeof(struct node));

        printf("Enter data of 1 node: ");
        scanf("%d", &data);

        head->data = data;
        head->next = NULL;

        temp = head;

        
        for(i=2; i<=n; i++)
        {
            newNode = (struct node *)malloc(sizeof(struct node));

            printf("Enter data of %d node: ", i);
            scanf("%d", &data);

            newNode->data = data;
            newNode->next = NULL;

            
            temp->next = newNode;

            
            temp = newNode;
        }

        
        temp->next = head;

        printf("\nCIRCULAR LINKED LIST CREATED SUCCESSFULLY\n");

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

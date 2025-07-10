#include <stdio.h>
#include <stdlib.h>
struct node {
    int data;
    struct node * prev;
    struct node * next;
}*head, *last;

void createList(int n);
void displayList();


void deleteFromN(int position);


int main()
{
    int n, data, choice=1;

    head = NULL;
    last = NULL;
    printf("Enter the total number of nodes in list: ");
    scanf("%d", &n);
    createList(n);
    
    
    printf("Enter the node position which you want to delete: ");
    scanf("%d", &n);
    deleteFromN(n);
    displayList();
    return 0;
}

void createList(int n)
{
    int i, data;
        struct node *newNode;
        head = (struct node *)malloc(sizeof(struct node));

        printf("Enter data of 1 node: ");
        scanf("%d", &data);

        head->data = data;
        head->prev = NULL;
        head->next = NULL;

        last = head;
        for(i=2; i<=n; i++)
        {
            newNode = (struct node *)malloc(sizeof(struct node));

            printf("Enter data of %d node: ", i);
            scanf("%d", &data);

            newNode->data = data;
            newNode->prev = last; 
            newNode->next = NULL;

            last->next = newNode; 
            last = newNode; 
        }
}

void displayList()
{
    struct node * temp;
    int n = 1;

    if(head == NULL)
    {
        printf("List is empty.\n");
    }
    else
    {
        temp = head;
        printf("DATA IN THE LIST:\n");

        while(temp != NULL)
        {
            printf("DATA of %d node = %d\n", n, temp->data);

            n++;

            
            temp = temp->next;
        }
    }
}

void deleteFromN(int position)
{
    struct node *current;
    int i;
    current = head;

    for(i=1; i<position && current!=NULL; i++)
    {
        current = current->next;
    }

    if(position == 1)
    {
        
        struct node * toDelete;
        toDelete = head;

        head = head->next; 
        head->prev = NULL; 

        free(toDelete); 
    }
    else if(current == last)
    {
        
        struct node * toDelete;
        toDelete = last;

        last = last->prev; 
        last->next = NULL; 

        free(toDelete);       
    }
    else if(current != NULL)
    {
        current->prev->next = current->next;
        current->next->prev = current->prev;

        free(current); 

        printf("SUCCESSFULLY DELETED NODE FROM %d POSITION.\n", position);
    }
}
    



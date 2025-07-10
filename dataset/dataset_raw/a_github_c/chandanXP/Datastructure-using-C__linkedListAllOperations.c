
#include <stdio.h>
#include <stdlib.h>

struct Node
{
     int data;          
     struct Node *next; 
};
void linkedListTraversal(struct Node *ptr)
{
     while (ptr != NULL)
     {
          printf("Element: %d\n", ptr->data);
          ptr = ptr->next;
     }
};


struct Node *insertAtFirst(struct Node *head, int data)
{
     struct Node *ptr = (struct Node *)malloc(sizeof(struct Node));
     ptr->next = head;
     ptr->data = data;
     return ptr;
};


struct Node *insertAtIndex(struct Node *head, int data, int index)
{
     struct Node *ptr = (struct Node *)malloc(sizeof(struct Node));
     struct Node *p = head;
     int i = 0;
     while (i != index - 1) 
     {
          p = p->next; 
          i++;
     }
     ptr->data = data;
     ptr->next = p->next;
     p->next = ptr;
     return head; 
};


struct Node *insertAtEnd(struct Node *head, int data)
{
     struct Node *ptr = (struct Node *)malloc(sizeof(struct Node));
     ptr->data = data;
     struct Node *p = head;
     while (p->next != NULL)
     {
          p = p->next;
     }
     p->next = ptr;
     ptr->next = NULL;
     return head; 
};

struct Node *insertAfterNode(struct Node *head, struct Node *previousNode, int data)
{
     struct Node *ptr = (struct Node *)malloc(sizeof(struct Node));
     ptr->data = data;
     ptr->next = previousNode->next;
     previousNode->next = ptr;
     return head; 
};


struct Node *deleteFirst(struct Node *head)
{
     struct Node *ptr = head;
     head = head->next;
     free(ptr);
     return head;
}

struct Node *deleteInBetween(struct Node *head, int index)
{
     struct Node *p = head;
     struct Node *q = head->next;
     for (int i = 0; i < index - 1; i++)
     {
          p = p->next;
          q = q->next;
     }
     p->next = q->next;
     free(q);
     return head;
}

struct Node *deleteLastNode(struct Node *head)
{
     struct Node *p = head;
     struct Node *q = head->next;
     while (q->next != NULL)
     {
          p = p->next;
          q = q->next;
     }
     p->next = NULL;
     free(q);
     return head;
}

struct Node *deleteByGivenKey(struct Node *head, int value)
{
     struct Node *p = head;
     struct Node *q = head->next;

     while (q->data != value && q->next != NULL)
     {
          p = p->next;
          q = q->next;
     }

     if (q->data == value)
     {
          p->next = q->next;
          free(q);
     }

     return head;
}

int main()
{
     
     struct Node *head;
     struct Node *second;
     struct Node *third;
     struct Node *fourth;

     
     head = (struct Node *)malloc(sizeof(struct Node));
     second = (struct Node *)malloc(sizeof(struct Node));
     third = (struct Node *)malloc(sizeof(struct Node));
     fourth = (struct Node *)malloc(sizeof(struct Node));

     
     head->data = 7;
     head->next = second;

     
     second->data = 11;
     second->next = third;

     
     third->data = 70;
     third->next = fourth;

     
     fourth->data = 22;
     fourth->next = NULL;

     printf("\nLinked list before insertion\n");
     linkedListTraversal(head);
     
     
     
     head = insertAfterNode(head, second, 45);
     printf("\nLinked list after insertion\n");
     linkedListTraversal(head);

     
     
     
     
     

     
     
     
     

     
     
     
     

     
     
     
     

     return 0;
}





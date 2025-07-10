

#include <stdio.h>
#include <stdlib.h>

struct Node
{
     int data;          
     struct Node *next; 
};

void linkedListTraversal(struct Node *head)
{
     struct Node *ptr = head;
     do
     {
          printf("Element is : %d\n", ptr->data);
          ptr = ptr->next;
     } while (ptr != head);
}

struct Node *insertAtEnd(struct Node *head, int data)
{
     struct Node *ptr = (struct Node *)malloc(sizeof(struct Node));
     ptr->data = data;
     struct Node *p = head->next;
     while (p->next != head)
     {
          p = p->next;
     }
     
     p->next = ptr;
     ptr->next = head;
     return head;
}

struct Node *insertAtTheIndex(struct Node *head, int data, int index)
{
     struct Node *ptr = (struct Node *)malloc(sizeof(struct Node));
     struct Node *q = head;
     int i = 0;
     while (i != index - 1)
     {
          q = q->next;
          i++;
     }
     ptr->data = data;
     ptr->next = q->next;
     q->next = ptr;
     return head;
}

struct Node *insertAtTheFirst(struct Node *head, int data)
{
     struct Node *ptr = (struct Node *)malloc(sizeof(struct Node));
     ptr->data = data;
     struct Node *p = head->next;
     while (p->next != head)
     {
          p = p->next;
     }
     
     ptr->next = p->next;
     p->next = ptr;
     return ptr;
}

struct Node *deleteFirst(struct Node *head)
{
     struct Node *ptr = head;
     
     struct Node *p = head->next;
     while (p->next != head)
     {
          p = p->next;
     }
     head = head->next; 
     p->next = head;    
     free(ptr);         
     return head;       
}

struct Node *deleteByGivenKey(struct Node *head, int value)
{
     struct Node *p = head;
     struct Node *q = head->next;

     while (q->data != value) 
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

struct Node *deleteLastNode(struct Node *head)
{
     struct Node *p = head;
     struct Node *q = head->next;
     while (q->next != head)
     { 
          p = p->next;
          q = q->next;
     }
     p->next = head; 
     free(q);        
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
     fourth->next = head;

     linkedListTraversal(head);

     

     head = insertAtEnd(head, 54);
     printf("---List After Insertion---\n");
     linkedListTraversal(head);

     
     
     

     
     
     

     
     
     

     
     
     

     
     
     

     return 0;
}





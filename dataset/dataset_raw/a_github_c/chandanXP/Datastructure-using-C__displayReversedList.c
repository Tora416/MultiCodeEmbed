#include<stdio.h>
#include<stdlib.h>

struct Node
{
     int data;
     struct Node *next;
};

void linkedListTreversal(struct Node*ptr){
     while (ptr!=NULL)
     {
          printf("Element : %d\n", ptr->data);
          ptr=ptr->next;
     }
     

}

struct Node *reversedList(struct Node *head){
     struct Node *p = head;
     printf("%d\n", p->data);
     struct Node *q = head->next;
     printf("%d\n", q->data);
     head=head->next;
     printf("%d\n", head->data);
     p->next=NULL;
     while (q->next!=NULL)
     {
          

          head=head->next;
          printf("b\n");

          
          

          q=q->next;
          printf("d\n");

          p=q->next;
          printf("a\n");

     }
     return head;
      
     
};


int main(){
     struct Node *head;
     struct Node *second;
     struct Node *third;
     struct Node *fourth;

     head = (struct Node *)malloc(sizeof(struct Node));
     second = (struct Node *)malloc(sizeof(struct Node));
     third = (struct Node *)malloc(sizeof(struct Node));
     fourth = (struct Node *)malloc(sizeof(struct Node));

     head->data=100;
     head->next=second;

     second ->data=200;
     second->next=third;

     third->data=300;
     third->next=fourth;

     fourth->data=400;
     fourth->next=NULL;

     printf("---Linked list before reverse---\n");
     linkedListTreversal(head);
     head = reversedList(head);
     printf("%d\n", head->data);
     printf("---Linked list after reverse---\n");
     linkedListTreversal(head);
 
     return 0;
}




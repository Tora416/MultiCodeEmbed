#include<stdio.h>
#include<stdlib.h>

struct InsertionAtGiven
{
     int data;
     struct InsertionAtGiven *next;  
};

void listTravesal(struct InsertionAtGiven*ptr){
     

     while (ptr!=NULL)
     {
          printf("%d\n", ptr->data);
          ptr=ptr->next;
     }
   
}

struct InsertionAtGiven* insertAfterValue(struct InsertionAtGiven*head, int info, int value){
     struct InsertionAtGiven*ptr=head;
     struct InsertionAtGiven*q= head->next;
     struct InsertionAtGiven*insert;
     insert->data=value;

     while (ptr->data!=info)
     {
         ptr=ptr->next;
         q=q->next;

     }
     ptr->next=insert;
     insert->next=q;
     return head;
      
}

int main(){
     struct InsertionAtGiven*head,
     *second,
     *third,
     *fourth,
     *fifth;

     head = (struct InsertionAtGiven * )malloc(sizeof(struct InsertionAtGiven));
     second = (struct InsertionAtGiven *)malloc(sizeof(struct InsertionAtGiven));
     third = (struct InsertionAtGiven *)malloc(sizeof( struct InsertionAtGiven));
     fourth = (struct InsertionAtGiven *)malloc(sizeof(struct InsertionAtGiven));
     fifth = (struct InsertionAtGiven *)malloc(sizeof(struct InsertionAtGiven));

     head->data=100;
     head->next=second;

     second->data=200;
     second->next=third;

     third->data=300;
     third->next=fourth;

     fourth->data=400;
     fourth->next=NULL;


     listTravesal(head);

     head = insertAfterValue(head, 200, 550);

     listTravesal(head);

  
     return 0;
}

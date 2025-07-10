#include<stdio.h>
#include<stdlib.h>


struct Node{
     int data;
     struct Node *next;
};

void linkedListtraversal(struct Node*ptr){
     while(ptr!=NULL){
          printf("%d\n", ptr->data);
          ptr=ptr->next;
     }

}

struct Node * deleteByInfo(struct Node*head, int value){
     struct Node*ptr=head;
     struct Node*q=head->next;
     while(q->data!=value){
          ptr=ptr->next;
          q=q->next;
     };
     ptr->next=q->next;
     free(q);
     return head; 
}

int main(){

     struct Node*head,
     *second,
     *third, 
     *fourth, 
     *fifth, 
     *sixth, 
     *seventh;

     head= (struct Node*)malloc(sizeof(struct Node));
     second = (struct Node*)malloc(sizeof(struct Node));
     third = (struct Node *)malloc(sizeof(struct Node));
     fourth = (struct Node*)malloc(sizeof(struct Node));
     fifth = (struct Node*)malloc(sizeof(struct Node));
     sixth = (struct Node*)malloc(sizeof(struct Node));
     seventh = (struct Node*)malloc(sizeof(struct Node));
 
     head->data =100;
     head->next = second;

     second->data= 200;
     second->next= third;

     third->data=300;
     third->next=fourth;

     fourth->data=400;
     fourth->next=fifth;

     fifth->data=500;
     fifth->next= sixth;

     sixth->data=600;
     sixth->next=seventh;

     seventh->data=700;
     seventh->next=NULL;

     linkedListtraversal(head);

     head = deleteByInfo(head, 300);

     linkedListtraversal(head);

}
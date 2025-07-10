#include<stdio.h>
#include<stdlib.h>

struct Node{
     int data;
     struct Node *next;

};
void linkedListTraversal(struct Node*ptr){
     while(ptr!=NULL){
          printf("Element: %d\n",ptr->data);
          ptr=ptr->next;
     }
}
struct Node * deleteFirst(struct Node * head){
     struct Node * ptr = head;
     head = head->next;
     free(ptr);
     return head;

}











 


struct Node * deleteInBetween(struct Node * head, int index){
     struct Node *p =head;
     struct Node *q = head->next;
     for (int i=0; i<index-1; i++){
          p= p->next;
          q=q->next;
     }
     p->next=q->next;
     free(q);
     return head;

}

struct Node * deleteLastNode(struct Node * head){
     struct Node *p = head;
     struct Node *q = head->next;
     while(q->next != NULL){
          p = p->next;
          q = q->next;
     }
     p->next = NULL;
     free(q);
     return head;

}

struct Node * deleteByGivenKey(struct Node * head, int value){
     struct Node *p = head;
     struct Node *q = head->next;

     while ( q->data != value && q->next != NULL)
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

int main(){
     
     struct Node*head;
     struct Node*second;
     struct Node*third;
     struct Node*fourth;
     struct Node*fifth;
     struct Node*sixth;
     struct Node*seventh;
 
     
     head = (struct Node *) malloc(sizeof(struct Node));
     second = (struct Node *) malloc(sizeof(struct Node));
     third = (struct Node *) malloc(sizeof(struct Node));
     fourth = (struct Node *) malloc(sizeof(struct Node));
     fifth = (struct Node *) malloc(sizeof(struct Node));
     sixth = (struct Node *) malloc(sizeof(struct Node));
     seventh = (struct Node *) malloc(sizeof(struct Node));

     
     head->data=7;
     head->next=second;

     
     second->data=11;
     second->next=third;

     
     third->data=70;
     third->next=fourth;

     
     fourth->data=22;
     fourth->next=fifth;

      
     fifth->data=44;
     fifth->next=sixth;

      
     sixth->data=20;
     sixth->next=seventh; 

     
     seventh->data=100;
     seventh->next=NULL;

     linkedListTraversal(head);

     
     
     
     

     
     
     
     

     
     
     
     

     
     head = deleteByGivenKey(head, 70);
     printf("---After deletion---\n");
     linkedListTraversal(head);

     return 0;
}





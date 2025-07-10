

#include<stdio.h>  
#include<stdlib.h>

typedef struct Node 
{
        int data; 
        struct Node *next; 
}node;

struct Node * insert(struct Node *head, int data, int index){
     struct Node * ptr = (struct Node *) malloc(sizeof(struct Node));
     struct Node * p = head;
     int i = 0;
     while (i!=index-1)
     {
          p = p->next;
          i++;
     }
     ptr->data = data;
     ptr->next = p->next;
     p->next = ptr;
     return head;

};

int find(node *ptr, int key)
{
        node *start = ptr;
        ptr =  ptr -> next; 
        
        while(ptr!=start)
        {
                if(ptr->data == key) 
                {
                        return 1;
                }
                ptr = ptr -> next;  
        }
        
        return 0;
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

void print(node *start,node *ptr)
{
        if(ptr==start)
        {
                return;
        }
        printf("%d ",ptr->data);
        print(start,ptr->next);
}
int main()
{
        
        node *start,*temp, *Head; 
        start = (node *)malloc(sizeof(node)); 
        temp = start;  
        temp -> next = start; 

 
        printf(" Linked List Example\n");
        printf("Choose List operation ");
           
        printf("1. Insert\n");
        printf("2. Delete\n");
        printf("3. Print\n");
        printf("4. Find\n");
        printf("5. EXIT\n");

        
        

 while(1)
        {
                printf(" Press your choice \n"); 

                int choice;  
                scanf("%d",&choice); 

                if(choice==1) 
                {
                        int data;
                        printf("The Element to be inserted in the list is: ");
                        scanf("%d",&data);
                        insert(struct node *start, int data, int index);
                }
                else if(choice==2)
                {
                        int data;
                        printf("The Element to be deleted from the list is: ");
                        scanf("%d",&data);
                        delete(start,data);   
                }
                else if(choice==3)
                {
                        printf("The list is ");
                        print(start,start->next);   
                        printf("\n");
                }
                else if(choice==4)
                {
                        int data;
                        printf("The Element is to be searched in the list is: ");
                        scanf("%d",&data);
                        int status = find(start,data);    
                        if(status)
                        {
                                printf("Element Found\n");
                        }
                        else
                        {
                                printf("Element Not Found\n");
                        }
                }
        else
                    break;
        }
}










#include"single_linked_list.h"


void print_list();


struct node
{
    char data;
    struct node *next;
};


struct node *head=NULL;
struct node *print_ptr=NULL;

int main()
{
    
    struct node *ptr1 = (struct node *)malloc(sizeof(struct node));
    ptr1->data = 'A';
    ptr1->next = NULL;

    
    struct node *ptr2 = (struct node *)malloc (sizeof(struct node));
    ptr2->data = 'B';
    ptr2->next = NULL;

    head = ptr1;
    
    ptr1->next = ptr2;

    
    printf("Before insertion\n");
    print_list();

    
    struct node *insert_ptr = (struct node *)malloc(sizeof(struct node));
    insert_ptr->data = 'C';
    insert_ptr->next = NULL;

    ptr2->next = insert_ptr;

    
    printf("After insertion\n");
    print_list();

    
    ptr2->next = NULL;

    printf("After deletion\n");
    print_list();

    
    free(ptr1);
    free(ptr2);
    free(insert_ptr);
}
void print_list()
{
    int index=0;
    print_ptr = head;
    while(print_ptr!=NULL)
    {
        
        index++;
        
        printf("Node Index %d Data value %c\n",index,print_ptr->data);
        
        print_ptr=print_ptr->next;
    }
}

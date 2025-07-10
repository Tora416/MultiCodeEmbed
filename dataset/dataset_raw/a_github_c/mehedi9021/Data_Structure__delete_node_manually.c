#include<stdio.h>
#include<stdlib.h>
struct node{
    int data;
    struct node*next;
};
struct node*head;

void print(){
struct node*temp;
temp=head;
while(temp!=NULL)
{
    printf("%d\n", temp->data);
    temp=temp->next;
}
}
void create(int value){
struct node*temp=(struct node*)malloc(sizeof(struct node));
temp->data=value;
temp->next=NULL;
if(head==NULL){
    head=temp;
}
else{
    struct node*newnode;
    newnode=head;
    while(newnode->next!=NULL)
    {
        newnode=newnode->next;
    }
    newnode->next=temp;
}
}
void deletenode(int position)
{
    int i;
    if(position==1)
    {
        struct node*temp;
        temp=head;
        head=head->next;
        free(temp);
    }
    else
    {
        struct node*temp1;
        temp1=head;
        for(i=1;i<=position-2;i++)
        {
            temp1=temp1->next;
        }
        struct node*temp2;
        temp2=temp1->next;
        temp1->next=temp2->next;
        free(temp2);
    }
}

int main()
{
    head=NULL;
    create(10);
    create(20);
    create(30);
    create(4);
    printf("display:\n");
    print();
    deletenode(2);
    printf("display:\n");
    print();
    return 0;


}

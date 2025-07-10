#include<stdio.h>
#include<stdlib.h>
struct node{
    int data;
    struct node*next;
};
struct node*head;

void createList(int n)
{
    struct node*mehedi;
    struct node*temp;
    int data, i;
    head=(struct node*)malloc(sizeof(struct node));
    printf("Enter node data:");
    scanf("%d", &data);
    head->data=data;
    head->next=NULL;
    temp=head;
    for(i=2;i<=n; i++)
    {
        mehedi=(struct node*)malloc(sizeof(struct node));
        printf("Enter node data:");
        scanf("%d", &data);
        mehedi->data=data;
        mehedi->next=NULL;
        temp->next=mehedi;
        temp=temp->next;
    }
}
void reverse()
{
    struct node* current, *prev, *temp;
    current=head;
    prev =NULL;
    while(temp!=NULL)
    {
        temp=current->next;
        current->next=prev;
        prev=current;
        current=temp;
    }
    head=prev;
}
void print(){
struct node*temp;
temp=head;
while(temp!=NULL)
{
    printf("%d\n", temp->data);
    temp=temp->next;
}
}
int main()
{
    int n;
    printf("Enter the total number of nodes: ");
    scanf("%d", &n);
    createList(n);
    printf("display:\n");
    print();
    printf("reverse:\n");
    reverse();
    print();
    return 0;


}



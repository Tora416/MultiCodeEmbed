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
void deletenode(int position)
{
        int i;

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
    return 0;


}



#include<stdio.h>
#include<stdlib.h>
struct node{
    int data;
    int key;
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

void print(){
struct node*temp;
temp=head;
while(temp!=NULL)
{
    printf("%d\n", temp->data);
    temp=temp->next;
}
}
void search(int key)
{
    struct node *temp;
    temp=head;
    while(temp!=NULL)
    {
        if(temp->data==key)
        {
            printf("Key found :)");
            temp=temp->next;
            break;
        }
        else
        {
            printf("Key not found :(");
            break;
        }
    }
}
int main()
{
    int n, key;
    printf("Enter the total number of nodes: ");
    scanf("%d", &n);
    createList(n);
    printf("display:\n");
    print();
    printf("srch:");
    scanf("%d", &key);
    search(key);
    return 0;


}


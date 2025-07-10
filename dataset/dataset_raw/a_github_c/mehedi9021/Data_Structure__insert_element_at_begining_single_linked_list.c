#include<stdio.h>
#include<stdlib.h>
struct node{
int data;
struct node*next;
};
struct node*head;
void createList(int n);
void inab(int data);
void displayList();
int main()
{
    int n, data;
    printf("Enter the total number of nodes: ");
    scanf("%d", &n);
    createList(n);

    printf("\nData in the list \n");
    displayList();
    printf("\nEnter data to insert at beginning of the list: ");
    scanf("%d", &data);
    inab(data);

    printf("\nData in the list \n");
    displayList();

    return 0;
}
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
void inab(int data)
{
    struct node*peloon;
    peloon=(struct node*)malloc(sizeof(struct node));
    peloon->data=data;
    peloon->next=head;
    head=peloon;
}
void displayList()
{
    struct node*temp;
    temp=head;
    while(temp!=NULL)
    {
        printf("%d\n", temp->data);
        temp=temp->next;
    }
}

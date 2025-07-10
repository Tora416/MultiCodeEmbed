#include<stdio.h>
#include<stdlib.h>
struct node{
int data;
struct node*next;
};
struct node*head;
void createlist(int n);
void displaylist();

int main()
    {
        int n,data;
        printf("Enter the number of list:");
        scanf("%d", &n);
        createlist(n);
        printf("\nDisplay\n");
        displaylist();
        return 0;
    }

void createlist(int n)
{
    struct node*mehedi;
    struct node*temp;
    int i, data;
    head=(struct node*)malloc(sizeof(struct node));
    printf("Enter data:");
    scanf("%d", &data);
    head->data=data;
    head->next=NULL;
    temp=head;
    for(i=2;i<=n;i++)
    {
        mehedi=(struct node*)malloc(sizeof(struct node));
        printf("Enter data:");
        scanf("%d", &data);
        mehedi->data=data;
        mehedi->next=NULL;
        temp->next=mehedi;
        temp=mehedi;
    }

}

    void displaylist()
    {
        struct node*temp;
        temp=head;
        while(temp!=NULL)
        {
            printf("%d\n", temp->data);
            temp=temp->next;
        }
    }




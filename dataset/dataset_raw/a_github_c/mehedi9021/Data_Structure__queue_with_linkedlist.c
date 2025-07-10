#include<stdio.h>
#include<stdlib.h>
struct Node {
    int data;
    struct Node* next;
};

struct Node* front = NULL;
struct Node* rear = NULL;


void Enqueue(int x) {
    struct Node* temp =
        (struct Node*)malloc(sizeof(struct Node));
    temp->data =x;
    temp->next = NULL;
    if(front == NULL && rear == NULL){
        front = rear = temp;
        return;
    }
    rear->next = temp;
    rear = temp;
}

void Dequeue() {
    struct Node* temp = front;
    if(front == NULL) {
        printf("Queue is Empty\n");
        return;
    }
    if(front == rear) {
        front = rear = NULL;
    }
    else {
        front = front->next;
    }
    free(temp);
}

int Front() {
    if(front == NULL) {
        printf("Queue is empty\n");
        return;
    }
    return front->data;
}

void Print() {
    struct Node* temp = front;
    while(temp != NULL) {
        printf("%d  \n",temp->data);
        temp = temp->next;
    }
    printf("\n");
}

int main()
{
    int i,n,p,m;
    printf("How many number do you want to enqueue ? ");
    scanf("%d",&n);
    for(i=0;i<n;i++)
    {
        printf("Enter the value :");
        scanf("%d",&p);
        Enqueue(p);
        printf("List is :\n");
        Print();
    }
    printf("How many number do you want to dequeue ? ");
    scanf("%d",&m);
    for(i=0;i<m;i++)
    {
        Dequeue();
        printf("List is :\n");
        Print();
    }

}

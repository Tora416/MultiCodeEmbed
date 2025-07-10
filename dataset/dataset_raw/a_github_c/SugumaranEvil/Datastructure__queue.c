






#include "queue.h"

#define SIZE 10

int queue[SIZE], front = -1, rear = -1;

void enqueue(void);
void dequeue(void);
void display(void);


int main()
{
    int choice;

    while(1){
        printf("Enter the choice\n1. Insertion\n2. Deletion\n3. Display\n4. Exit\n");
        scanf("%d",&choice);

        switch (choice){
            case 1:
                enqueue();
                break;
            case 2:
                dequeue();
                break;
            case 3:
                display();
                break;
            case 4:
                exit(0);
            default:
                printf("Invalid Choice\n");
        }
    }
}

void enqueue(void) {
    int value;
    printf("Enter the value to insert\n");
    scanf("%d",&value);

    if(rear == SIZE-1){
        printf("Queue is Full!!!\n");
    }else {
        if(front == -1)
            front = 0;
        rear = rear +1;
        queue[rear] = value;
        printf("Inserion Success..!!!\n");
    }
}

void dequeue(void) {
    if(front == rear)
        printf("Queue is Empty!!\n");
    else {
        printf("Dleted : %d",queue[front]);
        front = front+1;
        if(front == rear)
            front = rear = -1;
    }
}

void display(void){
    if(rear == -1)
        printf("Queue is empty\n");
    else {
        int i;
        printf("Queue elements are:\n");
        for(i=front; i<=rear; i++)
            printf("%d\t",queue[i]);
        printf("\n");
    }
}









#include"queue.h"

#define MAX 6

int arr[MAX];
int front =0;
int rear = -1;
int count = 0;


int peek()
{
    return arr[front];
}


int empty()
{
    if(count == 0)
        return 1;
    else
        return 0;
}


int full()
{
    if(count == MAX )
        return 1;
    else
        return 0;
}


int size()
{
    return count;
}


void insert(int data)
{
    if(full()==0)
    {
        if(rear == MAX-1)
            rear = -1;
        arr[++rear] = data;
        count++;
    }
    else
        printf("Queue is full\n");
}


int removedata()
{
    int data = arr[front++];
    if(front == MAX)
        front =0;
    count--;
    return data;
}

int main()
{
    
    insert(1);
    insert(2);
    insert(3);
    insert(4);
    insert(5);
    insert(6);

    int num = removedata();
    printf("%d \n",num);

    insert(7);
    
    while(!empty())
    {
        int n = removedata();
        printf("%d ",n);
    }
}
